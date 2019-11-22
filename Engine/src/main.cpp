#ifdef EMSCRIPTEN
    #define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <memory>
#include "Core/Engine.h"
#include "Display/Window.h"
#include "Display/Viewport.h"
#include "Assets/AssetManager.h"
#include "Shaders/Shader.h"
#include "Texturing/Texture.h"
#include "Geometry/Mesh.h"
#include "Geometry/Shapes/Quad.h"
#include "Materials/Material.h"
#include "ECS/Systems/TestSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Cameras/FPSCamera.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/ProgressHandler.hpp>

Mesh* processMesh(const aiScene* scene, aiMesh* object) {
    std::string name = object->mName.length != 0 ? std::string(object->mName.C_Str()) : "child_node";
    Mesh* mesh = new Mesh();
    mesh->setName(name.c_str());
    mesh->setVertexCount(object->mNumVertices);
    Material* meshMat = new Material(name.c_str());
    std::string textures_path = "/home/mel/Projects/VulkanLab/Resources/Textures";

    if (object->mMaterialIndex >= 0)
        aiMaterial *mat = scene->mMaterials[object->mMaterialIndex];

    mesh->setMaterial(meshMat);

    if (object->HasFaces())
    {
        for (unsigned int i = 0; i < object->mNumFaces; i++)
        {
            mesh->getIndices().push_back(object->mFaces[i].mIndices[0]);
            mesh->getIndices().push_back(object->mFaces[i].mIndices[1]);
            mesh->getIndices().push_back(object->mFaces[i].mIndices[2]);
        }
    }

    for (unsigned int i = 0; i < object->mNumVertices; i++)
    {
        if (object->HasPositions())
        {
            mesh->getVertices().push_back(object->mVertices[i].x);
            mesh->getVertices().push_back(object->mVertices[i].y);
            mesh->getVertices().push_back(object->mVertices[i].z);
        }

        if (object->HasNormals())
        {
            mesh->getNormals().push_back(object->mNormals[i].x);
            mesh->getNormals().push_back(object->mNormals[i].y);
            mesh->getNormals().push_back(object->mNormals[i].z);
        }

        if (object->HasTextureCoords(0))
        {
            mesh->getUvs().push_back(object->mTextureCoords[0][i].x);
            mesh->getUvs().push_back(object->mTextureCoords[0][i].y);
        }

        if (object->HasTangentsAndBitangents())
        {
            mesh->getTangents().push_back(object->mTangents[i].x);
            mesh->getTangents().push_back(object->mTangents[i].y);
            mesh->getTangents().push_back(object->mTangents[i].z);
        }
    }

    return mesh;
}

void processNode(std::vector<Mesh*>& meshes, aiNode* node, Node* parent, Node* newNode) {
    const char* name = node->mName.length != 0 ? node->mName.C_Str() : "child_node";

    newNode->name = name;
    newNode->transform->setMatrix(glm::mat4(node->mTransformation[0][0]));
    newNode->meshes.resize(node->mNumMeshes);

    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        newNode->meshes[i] = meshes[node->mMeshes[i]];

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
    {
        Node* n = new Node();
        n->name = node->mName.C_Str();
        std::cout << n->name << std::endl;
        newNode->children.push_back(n);
        processNode(meshes, node->mChildren[i], parent, newNode->children[i]);
    }
}

int main(int argc, char **argv) {

    const char *self_path = argv[0];

    // Init engine, assetsManager, scene & camera.
    Engine *engine = new Engine();
    AssetManager *assetManager = new AssetManager(self_path);
    Scene *scene = new Scene();
    FPSCamera *camera = new FPSCamera(engine->getViewport());
    scene->setActiveCamera(camera);

    // Parameter the scene ecs.
    scene->registerSystem<TestSystem>();
    auto entity = scene->createEntity();

    std::cout << "ENTITY ID: " << entity->getEntityId() << std::endl;
    auto transform = entity->assign<TransformComponent>();
    auto meshComponent = entity->assign<MeshComponent>();
    auto nodeComponent = entity->assign<NodeComponent>();

    engine->getScenesManager()->addScene(scene);

    // Create a new quad and assign a texture to it.
    Texture *texture = assetManager->load<Texture>("/home/mel/Projects/VulkanLab/Resources/Textures/omg.jpg", "omg");
    assetManager->load<Material>("material_path", "material_path");
    Shader *defaultShader = assetManager->load<Shader>("default", "default");
    Material *material = new Material("mat");
    material->setShader(defaultShader);
    Quad *quad = new Quad();
    quad->setMaterial(material);
//    transform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    meshComponent->mesh = quad;
//
//
    // Import tests
    Assimp::Importer importer;
    const char *meshToLoad = "/home/mel/Projects/VulkanLab/Resources/Shapes/cube.fbx";
    const aiScene *scn = importer.ReadFile(meshToLoad,
                                           aiProcess_CalcTangentSpace |
                                           //aiProcess_GenSmoothNormals |
                                           aiProcess_Triangulate |
                                           aiProcess_JoinIdenticalVertices |
                                           aiProcess_PreTransformVertices |
                                           aiProcess_RemoveRedundantMaterials |
                                           aiProcess_OptimizeMeshes |
                                           aiProcess_OptimizeGraph |
                                           aiProcess_ImproveCacheLocality);

    Node* rootNode = nullptr;
    std::vector<Mesh*> meshes = {};

    if (scn == nullptr) {
        std::cout << "Can't load mesh file: " << meshToLoad;
        std::cout << importer.GetErrorString() << std::endl;
    }
    else {
        if (scn->HasMeshes())
        {
            for (unsigned i = 0; i < scn->mNumMeshes; ++i) {
                Mesh* mesh = processMesh(scn, scn->mMeshes[i]);
                mesh->getMaterial()->setShader(defaultShader);
                auto loadedEntity = scene->createEntity();

                std::cout << "ENTITY ID: " << loadedEntity->getEntityId() << std::endl;
                auto transform = loadedEntity->assign<TransformComponent>();
                auto meshComponent = loadedEntity->assign<MeshComponent>();
                meshComponent->mesh = mesh;

                mesh->setupBuffers();
                meshes.resize(i);
                meshes.push_back(mesh);
            }
        }
        else
        {
            std::cout << "Error: No meshes found" << std::endl;
        }

        if (scn->mRootNode != NULL)
        {
            rootNode = new Node();
            rootNode->name = meshToLoad;
            processNode(meshes, scn->mRootNode, nullptr, rootNode);
            //resetRootNode();
        }
        else
        {
            std::cout << "Error loading model" << std::endl;
        }

        std::cout << "Loaded mesh: \"" << meshToLoad << "\"" << std::endl;
    }

    importer.FreeScene();

    // Parameter the shader texture sampler slot.
    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);
    texture->bind();

//    glfwMaximizeWindow(engine->getWindow()->getInstance());
//    glfwSetInputMode(engine->getWindow()->getInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Start the engine !
    engine->start();


    return 0;
}

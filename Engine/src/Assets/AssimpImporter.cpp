#include <vector>
#include <iostream>
#include "AssimpImporter.h"
#include "../Materials/Material.h"
#include "../Shaders/Shader.h"
#include "../Scene/Scene.h"
#include "../ECS/ECS.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/NodeComponent.h"

AssimpImporter::AssimpImporter() {

}

AssimpImporter::~AssimpImporter() {

}

void AssimpImporter::import(const char *filename, Scene *scene) {
    Assimp::Importer importer;
    const char *meshToLoad = filename;
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

    Node *rootNode = nullptr;
    std::vector<Mesh *> meshes = {};

    if (scn == nullptr) {
        std::cout << "Can't load mesh file: " << meshToLoad;
        std::cout << importer.GetErrorString() << std::endl;
    } else {
        if (scn->HasMeshes()) {
            for (unsigned i = 0; i < scn->mNumMeshes; ++i) {
                Mesh *mesh = processMesh(scn, scn->mMeshes[i]);
                Shader* shader = scene->getDefaultShader();

                if (shader != nullptr)
                    mesh->getMaterial()->setShader(shader);

                auto loadedEntity = scene->createEntity();

                std::cout << "ENTITY ID: " << loadedEntity->getEntityId() << std::endl;
                auto mt = loadedEntity->assign<TransformComponent>();
                auto mc = loadedEntity->assign<MeshComponent>();
                mc->mesh = mesh;

                mesh->setupBuffers();
                meshes.resize(i);
                meshes.push_back(mesh);
            }
        } else {
            std::cout << "Error: No meshes found" << std::endl;
        }

        if (scn->mRootNode != NULL) {
            rootNode = new Node();
            rootNode->name = meshToLoad;
            processNode(meshes, scn->mRootNode, nullptr, rootNode);
            //resetRootNode();
        } else {
            std::cout << "Error loading model" << std::endl;
        }

        std::cout << "Loaded mesh: \"" << meshToLoad << "\"" << std::endl;
    }

    importer.FreeScene();
}

Mesh *AssimpImporter::processMesh(const aiScene *scene, aiMesh *object) {
    std::string name = object->mName.length != 0 ? std::string(object->mName.C_Str()) : "child_node";
    Mesh *mesh = new Mesh();
    mesh->setName(name.c_str());
    mesh->setVertexCount(object->mNumVertices);
    Material *meshMat = new Material(name.c_str());
    std::string textures_path = "/home/mel/Projects/VulkanLab/Resources/Textures";

    if (object->mMaterialIndex >= 0)
        aiMaterial *mat = scene->mMaterials[object->mMaterialIndex];

    mesh->setMaterial(meshMat);

    if (object->HasFaces()) {
        for (unsigned int i = 0; i < object->mNumFaces; i++) {
            mesh->getIndices().push_back(object->mFaces[i].mIndices[0]);
            mesh->getIndices().push_back(object->mFaces[i].mIndices[1]);
            mesh->getIndices().push_back(object->mFaces[i].mIndices[2]);
        }
    }

    for (unsigned int i = 0; i < object->mNumVertices; i++) {
        if (object->HasPositions()) {
            mesh->getVertices().push_back(object->mVertices[i].x);
            mesh->getVertices().push_back(object->mVertices[i].y);
            mesh->getVertices().push_back(object->mVertices[i].z);
        }

        if (object->HasNormals()) {
            mesh->getNormals().push_back(object->mNormals[i].x);
            mesh->getNormals().push_back(object->mNormals[i].y);
            mesh->getNormals().push_back(object->mNormals[i].z);
        }

        if (object->HasTextureCoords(0)) {
            mesh->getUvs().push_back(object->mTextureCoords[0][i].x);
            mesh->getUvs().push_back(object->mTextureCoords[0][i].y);
        }

        if (object->HasTangentsAndBitangents()) {
            mesh->getTangents().push_back(object->mTangents[i].x);
            mesh->getTangents().push_back(object->mTangents[i].y);
            mesh->getTangents().push_back(object->mTangents[i].z);
        }
    }

    return mesh;
}

void AssimpImporter::processNode(std::vector<Mesh *> &meshes, aiNode *node, Node *parent, Node *newNode) {
    const char *name = node->mName.length != 0 ? node->mName.C_Str() : "child_node";

    newNode->name = name;
    newNode->transform->setMatrix(glm::mat4(node->mTransformation[0][0]));
    newNode->meshes.resize(node->mNumMeshes);

    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        newNode->meshes[i] = meshes[node->mMeshes[i]];

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        Node *n = new Node();
        n->name = node->mName.C_Str();
        std::cout << n->name << std::endl;
        newNode->children.push_back(n);
        processNode(meshes, node->mChildren[i], parent, newNode->children[i]);
    }
}

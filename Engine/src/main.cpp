#include <glad/glad.h>
#include <glm/glm.hpp>
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
    Texture *texture = assetManager->load<Texture>("/home/mel/Projects/VulkanLab/Resources/omg.jpg", "omg");
    assetManager->load<Material>("material_path", "material_path");
    Shader *defaultShader = assetManager->load<Shader>("default", "default");
    Material *material = new Material("mat");
    material->setShader(defaultShader);
    Quad *quad = new Quad();
    quad->setMaterial(material);
//    transform->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    meshComponent->mesh = quad;


    // Import tests
    Assimp::Importer importer;
    const char *meshToLoad = "/home/mel/Projects/VulkanLab/Resources/cube.obj";
    const aiScene *scn = importer.ReadFile(meshToLoad,
                                           aiProcess_CalcTangentSpace |
                                           aiProcess_Triangulate |
                                           aiProcess_JoinIdenticalVertices |
                                           aiProcess_SortByPType);
    if (!scn) {
        std::cout << "Failed to load mesh: \"" << meshToLoad << "\", " << importer.GetErrorString() << std::endl;
    } else {
        std::cout << "Loaded mesh: \"" << meshToLoad << "\"" << std::endl;
    }

    // Parameter the shader texture sampler slot.
    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);
    texture->bind();

    // Start the engine !
    engine->start();

    return 0;
}

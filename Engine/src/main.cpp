#ifdef EMSCRIPTEN
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <memory>
#include <thread>
#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Core/Engine.h"
#include "Display/Window.h"
#include "Assets/AssetManager.h"
#include "Shaders/Shader.h"
#include "Texturing/Texture.h"
#include "Geometry/Mesh.h"
#include "Geometry/Shapes/Quad.h"
#include "Materials/Material.h"
#include "ECS/Systems/TestSystem.h"
#include "Scene/Scene.h"
#include "Cameras/FPSCamera.h"
#include "Lighting/Light.h"
#include "Assets/AssimpImporter.h"
#include "Assets/FontImporter.h"
#include "Interface/NanoGui.h"

int main(int argc, char **argv) {
    const char *self_path = argv[0];

    // Init engine, assetsManager, scene & camera.
    Engine *engine = new Engine();
    AssetManager *assetManager = new AssetManager(self_path);
    Scene *scene = new Scene();
    FPSCamera *camera = new FPSCamera(engine->getViewport());

    camera->setPosition(glm::vec3(0.158099f, 2.068612f, 1.410623f));
    camera->setYaw(267.901f);
    camera->setPitch(-52.8999f);

    scene->setActiveCamera(camera);

    // Create some light entities.
    auto pointLight = scene->createEntity();
    pointLight->assign<PointLightComponent>();

    // Parameter the scene ecs.
    scene->registerSystem<TestSystem>();


    // Create a new quad and assign a texture to it.
    Texture *texture = assetManager->load<Texture>(
        "/home/mel/Projects/VulkanLab/Resources/Textures/container_diffuse.png", "omg");
    assetManager->load<Material>("material_path", "material_path");
    Shader *defaultShader = assetManager->load<Shader>("default", "default");
    scene->setDefaultShader(defaultShader);

    Material *material = new Material("mat");
    material->setShader(defaultShader);

    auto entity = scene->createEntity();
    std::cout << "ENTITY ID: " << entity->getEntityId() << std::endl;
    auto tr = entity->assign<TransformComponent>();
    auto meshComponent = entity->assign<MeshComponent>();
    auto nodeComponent = entity->assign<NodeComponent>();
    tr->transform->setScale(glm::vec3(2.0f));
    Quad *quad = new Quad();
    quad->setMaterial(material);
    meshComponent->mesh = quad;

    assetManager->load<Mesh>("/home/mel/Projects/VulkanLab/Resources/webatrio.obj", "webatrio", scene);
    assetManager->load<Font>("/home/mel/Android/Sdk/platforms/android-29/data/fonts/Roboto-Light.ttf", "roboto_light");

    // Parameter the shader texture sampler slot.
    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);
    texture->bind();

    engine->getScenesManager()->addScene(scene);

//    auto nanogui = new NanoGui(engine);

    // Start the engine !
    engine->start();

    return 0;
}

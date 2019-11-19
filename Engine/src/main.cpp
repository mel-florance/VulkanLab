#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core/Engine.h"
#include "Display/Window.h"
#include "Display/Viewport.h"
#include "Assets/AssetManager.h"
#include "Shaders/Shader.h"
#include "Texturing/Texture.h"
#include "Geometry/Mesh.h"
#include "Materials/Material.h"
#include "Buffers/ArrayBuffer.h"
#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"

//#include "ECS/ECS.h"
//#include "ECS/Systems/TestSystem.h"
//ECS_TYPE_IMPLEMENTATION;
//using namespace ECS;
#include "ECS/Systems/TestSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

int main(int argc, char **argv) {

    // Initialize engine classes.
    const char *self_path = argv[0];

    Engine *engine = new Engine();
    AssetManager *am = new AssetManager(self_path);

    Scene* scene = new Scene();
    scene->registerSystem<TestSystem>();
    auto entity = scene->createEntity();

    std::cout << "ENTITY ID: " << entity->getEntityId() << std::endl;
    auto transform = entity->assign<Transform>();
    scene->update();
    scene->update();

    std::cout << glm::to_string(transform->position) << std::endl;

    engine->getScenesManager()->addScene(scene);

    // Load some stuff.
    am->load<Texture>("/home/mel/Projects/VulkanLab/Resources/omg.jpg", "omg");
    am->load<Material>("material_path", "material_path");
    Shader *defaultShader = am->load<Shader>("default", "default");

    Mesh *triangle = new Mesh();

    // Create mesh vertices of a plane
    std::vector vertices = {
        // First triangle
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.5f,
        // Second triangle
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f
    };

    // Create mesh uv coordinates of a plane
    std::vector uvs = {
        // First triangle
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        // Second triangle
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    triangle->setVertices(vertices);
    triangle->setUvs(uvs);

    // Bind the new shader.
    defaultShader->bind();

    // Create the main array buffer.
    ArrayBuffer *vao = new ArrayBuffer();
    vao->bind();

    // Create a vertex buffer for the vertices to be store.
    VertexBuffer *vbo_position = new VertexBuffer();
    vbo_position->bind();
    vbo_position->setData(vertices.data(), vertices.size() * sizeof(float));

    // Create a position attribute for the vertices.
    VertexBuffer::AttributeData *position_attribute = new VertexBuffer::AttributeData();
    position_attribute->index = 0;
    position_attribute->size = 3;
    vbo_position->setAttribute(position_attribute);

    // Create a vertex buffer for the uvs to be store.
    VertexBuffer *vbo_uvs = new VertexBuffer();
    vbo_uvs->bind();
    vbo_uvs->setData(uvs.data(), uvs.size() * sizeof(float));

    // Create a uv coordinate attribute for the uvs.
    VertexBuffer::AttributeData *texture_attribute = new VertexBuffer::AttributeData();
    texture_attribute->index = 1;
    texture_attribute->size = 2;
    vbo_uvs->setAttribute(texture_attribute);

//    // Index buffer
//    IndexBuffer *indexBuffer = new IndexBuffer();
//    indexBuffer->setData(indices, sizeof(indices));

    defaultShader->bind();
    defaultShader->setUniform1i("textureMap", 0);
//        texture->bind();

//    World* world = World::createWorld();
//    EntitySystem* testSystem = world->registerSystem(new TestSystem());
//    Entity* ent = world->create();
//    auto pos = ent->assign<Position>(0.f, 0.f);
//    auto rot = ent->assign<Rotation>(0.f);
//
//    std::cout << "Initial values: position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;
//
//    world->tick(10.f);
//
//    std::cout << "After tick(10): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;
//
//    world->disableSystem(testSystem);
//
//    world->tick(10.f);
//
//    std::cout << "After tick(10) and DisableSystem(testSystem): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;
//
//    world->enableSystem(testSystem);
//
//    world->tick(10.f);
//
//    std::cout << "After tick(10) and EnableSystem(testSystem): position(" << pos->x << ", " << pos->y << "), rotation(" << rot->angle << ")" << std::endl;
//
//    ent->remove<Position>();
//    ent->remove<Rotation>();
//
//    std::cout << "Creating more entities..." << std::endl;
//
//    for (int i = 0; i < 10; ++i)
//    {
//        ent = world->create();
//        ent->assign<SomeComponent>();
//    }
//
//    int count = 0;
//    std::cout << "Counting entities with SomeComponent..." << std::endl;
//    // range based for loop
//    for (auto ent : world->each<SomeComponent>())
//    {
//        ++count;
//        std::cout << "Found entity #" << ent->getEntityId() << std::endl;
//    }
//
//    std::cout << count << " entities have SomeComponent!" << std::endl;
//
//    // Emitting events
//    world->emit<SomeEvent>({ 4 });
//
//    std::cout << "We have " << world->getCount() << " entities right now." << std::endl;
//    world->cleanup();
//    std::cout << "After a cleanup, we have " << world->getCount() << " entities." << std::endl;
//
//    std::cout << "Destroying the world..." << std::endl;
//
//    world->destroyWorld();
//

    engine->start();

//    // Main render loop
//    window->update([=](glm::ivec2 &size) {
//        viewport->setSize(size);
//        viewport->apply();
//        viewport->clear();
//
//        texture->bind();
//        vao->bind();
//        triangle->draw();
//    });

//    delete window;

    return 0;
}

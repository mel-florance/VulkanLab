#include <iostream>
#include <type_traits>
#include <glm/gtx/string_cast.hpp>
#include "Engine.h"
#include "../Display/Viewport.h"
#include "../Display/Window.h"
#include "../Rendering/Renderer.h"

#include "../Cameras/Camera.h"
#include "../Cameras/FPSCamera.h"
#include "../Scene/Scene.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/MeshComponent.h"

Loop *Engine::loop = nullptr;
SceneManager *Engine::scenesManager = new SceneManager();
Viewport *Engine::viewport = nullptr;

Engine::Engine() {

    this->loop = new Loop(this);
    this->loop->setUpdateCallback(&Engine::update);
    this->loop->setRenderCallback(&Engine::render);
    this->window = new Window();

    this->viewport = new Viewport(this->window);
    this->renderer = new Renderer(this);

    this->network = new Network();
}

Engine::~Engine() {
    delete this->renderer;
    delete this->viewport;
}

void Engine::start() {
    Engine::loop->start();
}

void Engine::stop() {
    Engine::loop->stop();
}

void Engine::update(Loop *loop, Engine *self) {
    glfwPollEvents();
    double delta = loop->getPassedTime();
    Scene *scene = self->scenesManager->getActiveScene();
    Camera *camera = scene->getActiveCamera();
    camera->update(delta);
    scene->update(delta);

//    FPSCamera* cam = (FPSCamera*)camera;

//    std::cout << "Position: " << glm::to_string(cam->getPosition()) << std::endl;
//    std::cout << "Yaw: " << cam->getYaw() << std::endl;
//    std::cout << "Pitch: " << cam->getPitch() << std::endl;

    scene->getWorld()->each<TransformComponent, MeshComponent>(
        [&](
            Entity *entity,
            ComponentHandle<TransformComponent> transformComponent,
            ComponentHandle<MeshComponent> meshComponent
        ) {
            transformComponent->transform->setRotation(glm::vec3(glm::radians(90.0f), /*glfwGetTime() / 2.0f,*/0.0f, 0.0f));
        });
}

void Engine::render(Loop *loop, Engine *self) {
    self->renderer->render();
    glfwSwapBuffers(self->window->getInstance());
}

void Engine::onEvent(EventType eventType, Event *data) {
    Scene *scene = Engine::scenesManager->getActiveScene();
    FPSCamera *camera = (FPSCamera *) scene->getActiveCamera();

    if (camera != nullptr) {
        switch (eventType) {
            case onMouseButton:
                camera->onMouseButton(data);
                break;
            case onMouseMove:
                camera->onMouseMove(data);
                break;
            case onMouseScroll:
                camera->onMouseScroll(data);
                break;
            case onKeyboardInput:
                camera->onKeyboardInput(data);
                break;
            case onKeyboardChar:
                break;
            case onWindowDrop:
                break;
            case onWindowClose:
                break;
            case onWindowCursorEnter:
                break;
            case onWindowResize:
                camera->onWindowResize(data);
                WindowEvents* e = (WindowEvents*)data;
                Engine::viewport->setSize(glm::vec2(e->width, e->height));
                Engine::viewport->apply();
                break;
        }
    }
}
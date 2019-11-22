#include <iostream>
#include <type_traits>
#include "Engine.h"
#include "../Display/Viewport.h"
#include "../Display/Window.h"
#include "../Rendering/Renderer.h"
#include "../Scene/SceneManager.h"
#include "../Cameras/Camera.h"
#include "../Cameras/FPSCamera.h"
#include "../Scene/Scene.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/MeshComponent.h"

Loop *Engine::loop = nullptr;
SceneManager *Engine::scenesManager = nullptr;

Engine::Engine() {

    this->loop = new Loop(this);
    this->loop->setUpdateCallback(&Engine::update);
    this->loop->setRenderCallback(&Engine::render);
    this->window = new Window();

    this->viewport = new Viewport(this->window);
    this->renderer = new Renderer(this);
    this->scenesManager = new SceneManager();

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

    scene->getWorld()->each<TransformComponent, NodeComponent, MeshComponent>(
        [&](
            Entity *entity,
            ComponentHandle<TransformComponent> transformComponent,
            ComponentHandle<NodeComponent> nodeComponent,
            ComponentHandle<MeshComponent> meshComponent
        ) {
//            transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 10.0f));
//            transform = glm::scale(transform, glm::vec3(0.5f, -0.5f, 0.0f));
//            transform = glm::rotate(transform, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//            transform = glm::rotate(transform, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
//            transform = glm::rotate(transform, (float) cosf(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
//            transformComponent->transform->setRotation(glm::vec3(glfwGetTime()));
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
            case onWindowResize:
                camera->onWindowResize(data);
                break;
            case onWindowDrop:
                break;
            case onWindowClose:
                break;
            case onWindowCursorEnter:
                break;
        }
    }
}
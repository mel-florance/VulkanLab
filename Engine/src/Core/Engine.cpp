#include <iostream>
#include "Engine.h"
#include "../Display/Viewport.h"
#include "../Display/Window.h"
#include "../Rendering/Renderer.h"
#include "../Scene/SceneManager.h"

Loop* Engine::loop = nullptr;

Engine::Engine() {
    this->loop = new Loop(this);
    this->loop->setUpdateCallback(&Engine::update);
    this->loop->setRenderCallback(&Engine::render);

    this->window = new Window();
    this->viewport = new Viewport(this->window);
    this->renderer = new Renderer(this->viewport);
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

void Engine::update(Loop* loop, Engine* self) {
//    double delta = loop->getPassedTime();
}

void Engine::render(Loop* loop, Engine* self) {
    self->renderer->render();
    glfwSwapBuffers(self->window->getInstance());
    glfwPollEvents();
 }
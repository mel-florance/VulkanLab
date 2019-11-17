#include <iostream>
#include "Engine.h"
#include "../Display/Viewport.h"
#include "../Rendering/Renderer.h"

Engine::Engine() {
    this->loop = new Loop(this);
    this->loop->setUpdateCallback(&Engine::update);
    this->loop->setRenderCallback(&Engine::render);
    this->viewport = new Viewport();
    this->renderer = new Renderer(this->viewport);
}

Engine::~Engine() {
    delete this->renderer;
    delete this->viewport;
}

void Engine::start() {
    this->loop->start();
}

void Engine::stop() {
    this->loop->stop();
}

void Engine::update(Loop* loop, Engine* self) {
    double delta = loop->getPassedTime();
}

void Engine::render(Loop* loop, Engine* self) {
    self->renderer->render();
}
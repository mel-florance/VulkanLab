#ifndef VULKANLAB_ENGINE_H
#define VULKANLAB_ENGINE_H

#include "Loop.h"

class Engine {
public:
    Engine() {
        this->loop = new Loop(this);
        this->loop->setUpdateCallback(&Engine::update);
        this->loop->setRenderCallback(&Engine::render);
    }

    ~Engine() {

    }

    void start() {
        this->loop->start();
    }

    void stop() {
        this->loop->stop();
    }

    static void update(Loop* loop, Engine* self) {
        double delta = loop->getPassedTime();
    }

    static void render(Loop* loop, Engine* self) {

    }

private:
    Loop* loop;
};

#endif //VULKANLAB_ENGINE_H

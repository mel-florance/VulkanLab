#ifndef VULKANLAB_RENDERER_H
#define VULKANLAB_RENDERER_H

class Engine;

class Renderer {
public:
    Renderer(Engine* engine);
    ~Renderer();

    void render();

private:
    Engine* engine;
};

#endif //VULKANLAB_RENDERER_H

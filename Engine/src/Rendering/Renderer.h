#ifndef VULKANLAB_RENDERER_H
#define VULKANLAB_RENDERER_H

class Viewport;

class Renderer {
public:
    Renderer(Viewport* viewport);
    ~Renderer();

    void render();

    inline Viewport *getViewport() const {
        return viewport;
    }

    inline void setViewport(Viewport *viewport) {
        Renderer::viewport = viewport;
    }

private:
    Viewport* viewport;
};

#endif //VULKANLAB_RENDERER_H

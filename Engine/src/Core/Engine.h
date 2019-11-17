#ifndef VULKANLAB_ENGINE_H
#define VULKANLAB_ENGINE_H

#include "Loop.h"

class Viewport;
class Renderer;

class Engine {
public:
    Engine();
    ~Engine();

    /**
     * Start the engine
     */
    void start();

    /**
     * Stop the engine
     */
    void stop();

    /**
     * Update routine of the engine
     * @param loop
     * @param self
     */
    static void update(Loop* loop, Engine* self);

    /**
     * Call the attached renderer.
     * @param loop
     * @param self
     */
    static void render(Loop* loop, Engine* self);

    /**
     * Return the engine loop.
     * @return
     */
    inline Loop *getLoop() const {
        return loop;
    }

    /**
     * Set the engine loop.
     * @param loop
     */
    inline void setLoop(Loop *loop) {
        Engine::loop = loop;
    }

    /**
     * Return the currently attached viewport.
     * @return
     */
    inline Viewport *getViewport() const {
        return viewport;
    }

    /**
     * Set the viewport to display to.
     * @param viewport
     */
    inline void setViewport(Viewport *viewport) {
        Engine::viewport = viewport;
    }

    /**
     * Return the currently attached renderer.
     * @return
     */
    inline Renderer *getRenderer() const {
        return renderer;
    }

    /**
     * Set the renderer used to draw.
     * @param renderer
     */
    inline void setRenderer(Renderer *renderer) {
        Engine::renderer = renderer;
    }

private:
    Loop* loop;
    Viewport* viewport;
    Renderer* renderer;
};

#endif //VULKANLAB_ENGINE_H

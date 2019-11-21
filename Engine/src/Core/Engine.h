#ifndef VULKANLAB_ENGINE_H
#define VULKANLAB_ENGINE_H

#include <memory>
#include "Loop.h"
#include "../Events/Event.h"

class Viewport;

class Renderer;

class Window;

class SceneManager;

class Engine {
public:
    Engine();

    ~Engine();

    /**
     * Start the engine
     */
    static void start();

    /**
     * Stop the engine
     */
    static void stop();

    /**
     * Update routine of the engine
     * @param loop
     * @param self
     */
    static void update(Loop *loop, Engine *self);

    /**
     * Call the attached renderer.
     * @param loop
     * @param self
     */
    static void render(Loop *loop, Engine *self);

    /**
     * When an event occurs.
     */
    static void onEvent(EventType event, Event* data);

    /**
     * Return the engine loop.
     * @return
     */
    inline Loop *getLoop() const {
        return this->loop;
    }

    /**
     * Set the engine loop.
     * @param loop
     */
    inline void setLoop(Loop *loop) {
        this->loop = loop;
    }

    /**
     * Return the currently attached viewport.
     * @return
     */
    inline Viewport *getViewport() const {
        return this->viewport;
    }

    /**
     * Set the viewport to display to.
     * @param viewport
     */
    inline void setViewport(Viewport *viewport) {
        this->viewport = viewport;
    }

    /**
     * Return the currently attached renderer.
     * @return
     */
    inline Renderer *getRenderer() const {
        return this->renderer;
    }

    /**
     * Set the renderer used to draw.
     * @param renderer
     */
    inline void setRenderer(Renderer *renderer) {
        this->renderer = renderer;
    }

    /**
     * Return the current window
     * @return
     */
    inline Window *getWindow() const {
        return this->window;
    }

    /**
     * Set the current window
     */
    inline void setWindow(Window *window) {
        this->window = window;
    }

    /**
     * Return a reference to the scenesManager pointer.
     */
    inline SceneManager *getScenesManager() {
        return this->scenesManager;
    }

    static Loop *loop;
    static SceneManager *scenesManager;

private:
    Window *window;
    Viewport *viewport;
    Renderer *renderer;
};

#endif //VULKANLAB_ENGINE_H

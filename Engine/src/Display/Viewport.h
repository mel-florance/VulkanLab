#ifndef VULKANLAB_VIEWPORT_H
#define VULKANLAB_VIEWPORT_H


#include <glm/glm.hpp>

class Window;

class Viewport {
public:
    /**
     * Viewport constructor
     */
    Viewport(Window* window) : window(window) {
        this->setColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    }

    /**
     * Viewport destructor
     */
    ~Viewport() {

    }

    /**
     * Clear the viewport.
     */
    static void clear();

    /**
     * Apply the viewport dimensions to the gpu.
     */
    void apply();

    /**
     * Return the size of the viewport.
     * @return
     */
    const glm::vec2 &getSize() const {
        return size;
    }

    /**
     * Set the dimensions of the viewport.
     */
    void setSize(const glm::vec2 &size) {
        this->size = size;
    }

    /**
     * Return the clear color of the viewport.
     */
    const glm::vec4 &getColor() const {
        return color;
    }

    /**
     * Set the clear color of the viewport.
     */
    void setColor(const glm::vec4 &color);

    /**
     * Return the current viewport window.
     */
    inline Window *getWindow() const {
        return window;
    }

    /**
     * Set the current viewport window.
     */
    inline void setWindow(Window *window) {
        Viewport::window = window;
    }

private:
    Window* window;
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
};

#endif //VULKANLAB_VIEWPORT_H

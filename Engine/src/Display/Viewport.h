#ifndef VULKANLAB_VIEWPORT_H
#define VULKANLAB_VIEWPORT_H

#include <memory>
#include <glm/glm.hpp>

class Window;

class Viewport {
public:
    /**
     * Viewport constructor
     */
    Viewport(Window *window);

    /**
     * Viewport destructor
     */
    ~Viewport();

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
    inline const glm::vec2 &getSize() const {
        return this->size;
    }

    /**
     * Set the dimensions of the viewport.
     */
    inline void setSize(const glm::vec2 &size) {
        this->size = size;
    }

    /**
     * Return the clear color of the viewport.
     */
    inline const glm::vec4 &getColor() const {
        return this->color;
    }

    /**
     * Set the clear color of the viewport.
     */
    void setColor(const glm::vec4 &color);

    /**
     * Return the current viewport window.
     */
    inline Window *getWindow() const {
        return this->window;
    }

    /**
     * Set the current viewport window.
     */
    void setWindow(Window *window);

private:
    Window *window;
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
};

#endif //VULKANLAB_VIEWPORT_H

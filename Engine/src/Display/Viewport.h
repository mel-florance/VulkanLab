#ifndef VULKANLAB_VIEWPORT_H
#define VULKANLAB_VIEWPORT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Viewport {
public:
    /**
     * Viewport constructor
     */
    Viewport() {

    }

    /**
     * Viewport destructor
     */
    ~Viewport() {

    }

    /**
     * Clear the viewport.
     */
    static inline void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /**
     * Apply the viewport dimensions to the gpu.
     */
    inline void apply() {
        glViewport(position.x, position.y, size.x, size.y);
    }

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
    void setColor(const glm::vec4 &color) {
        this->color = color;
        glClearColor(color.r, color.g, color.b, color.a);
    }

private:
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
};

#endif //VULKANLAB_VIEWPORT_H

#ifndef VULKANLAB_VIEWPORT_H
#define VULKANLAB_VIEWPORT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Viewport {
public:
    /**
     * Viewport constructor
     * @param color
     * @param position
     * @param size
     */
    Viewport(
            const glm::vec4 &color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
            const glm::vec2 &position = glm::vec2(0.0f),
            const glm::vec2 &size = glm::vec2(0.0f)
    );

    /**
     * Viewport destructor
     */
    ~Viewport();

    /**
     * Return the viewport clear color.
     * @return
     */
    inline glm::vec4 &getClearColor() {
        return this->clearColor;
    }

    /**
     * Set the viewport color with RGBA format.
     * @param color
     */
    inline void setClearColor(const glm::vec4 &color) {
        this->clearColor = color;
        glClearColor(color.r, color.g, color.b, color.a);
    }

    /**
     * Return the anchor position of the viewport.
     * @return
     */
    inline glm::vec2 &getPosition() {
        return this->position;
    }

    /**
     * Set the anchor position of the viewport.
     * @param pos
     */
    inline void setPosition(const glm::vec2 &pos) {
        this->position = pos;
    }

    /**
     * Return the dimensions of the viewport.
     * @return
     */
    inline glm::vec2 &getSize() {
        return this->size;
    }

    /**
     * Set the dimensions of the viewport.
     * @param value
     */
    inline void setSize(const glm::vec2 &value) {
        this->size = value;
    }

    /**
     * Apply the transform of the viewport to the current frame buffer.
     */
    inline void apply() {
        glViewport(
                this->position.x,
                this->position.y,
                this->size.x,
                this->size.y
        );
    }

    /**
     * Clear the viewport.
     */
    static inline void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

private:
    glm::vec4 clearColor;
    glm::vec2 position;
    glm::vec2 size;
};

#endif //VULKANLAB_VIEWPORT_H

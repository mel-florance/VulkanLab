#ifndef VULKANLAB_QUAD_H
#define VULKANLAB_QUAD_H

#include "../Mesh.h"
#include "../../Buffers/ArrayBuffer.h"
#include "../../Buffers/VertexBuffer.h"
#include <glm/glm.hpp>

class Quad : public Mesh {
public:
    /**
     * Quad constructor
     */
    Quad() : Mesh(), size(glm::vec2(1.0f, 1.0f)) {
        this->setVertices({
          // First triangle
          -size.x, size.y, 1.0f,
          -size.x, -size.y, 1.0f,
          size.x, -size.y, 1.0f,
          // Second triangle
          -size.x, size.y, 1.0f,
          size.x, -size.y, 1.0f,
          size.x, size.y, 1.0f
        });

        this->setUvs({
             // First triangle
             0.0f, 1.0f,
             0.0f, 0.0f,
             1.0f, 0.0f,
             // Second triangle
             0.0f, 1.0f,
             1.0f, 0.0f,
             1.0f, 1.0f
        });

        setupBuffers();
    }

    /**
     * Return the size of the quad.
     */
    inline const glm::vec2 &getSize() const {
        return this->size;
    }

    /**
     * Set the size of the quad.
     */
    inline void setSize(const glm::vec2 &size) {
        this->size = size;
    }

private:
    glm::vec2 size;
};

#endif //VULKANLAB_QUAD_H

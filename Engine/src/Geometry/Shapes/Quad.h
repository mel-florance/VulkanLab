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

        ArrayBuffer *vao = new ArrayBuffer();
        vao->bind();
        this->addArrayBuffer(vao);

        VertexBuffer *vbo_position = new VertexBuffer();
        vbo_position->bind();
        vbo_position->setData(this->vertices.data(), this->vertices.size() * sizeof(float));

        // Create a position attribute for the vertices.
        VertexBuffer::AttributeData *position_attribute = new VertexBuffer::AttributeData();
        position_attribute->index = 0;
        position_attribute->size = 3;
        vbo_position->setAttribute(position_attribute);
        this->addBuffer(vao, vbo_position);

        // Create a vertex buffer for the uvs to be store.
        VertexBuffer *vbo_uvs = new VertexBuffer();
        vbo_uvs->bind();
        vbo_uvs->setData(uvs.data(), uvs.size() * sizeof(float));

        // Create a uv coordinate attribute for the uvs.
        VertexBuffer::AttributeData *texture_attribute = new VertexBuffer::AttributeData();
        texture_attribute->index = 1;
        texture_attribute->size = 2;
        vbo_uvs->setAttribute(texture_attribute);
        this->addBuffer(vao, vbo_uvs);
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

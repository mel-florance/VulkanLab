#ifndef VULKANLAB_VERTEX_BUFFER_H
#define VULKANLAB_VERTEX_BUFFER_H

#include <glad/glad.h>

class VertexBuffer {
public:
    /**
     * VertexBuffer constructor
     */
    VertexBuffer() {
        glGenBuffers(1, &this->id);
    }

    /**
     * VertexBuffer destructor
     */
    ~VertexBuffer() {
        glDeleteBuffers(1, &this->id);
    }

    struct AttributeData {
        GLuint index = 0;
        GLint size = 0;
        GLenum type = GL_FLOAT;
        GLboolean normalized = GL_FALSE;
        GLsizei stride = 0;
        void *pointer = nullptr;
    };

    /**
     * Push data to the vertex buffer.
     * @param data
     * @param mode
     */
    inline void setData(void *data, GLsizei size, int mode = GL_STATIC_DRAW) {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /**
     * Set a specific attribute on the vertex buffer.
     * @param data
     */
    static inline void setAttribute(AttributeData *data) {
        glVertexAttribPointer(
                data->index,
                data->size,
                data->type,
                data->normalized,
                data->stride,
                data->pointer
        );
    }

    /**
     * Bind the vertex buffer.
     */
    inline void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
    }

private:
    unsigned int id;
};

#endif //VULKANLAB_VERTEX_BUFFER_H

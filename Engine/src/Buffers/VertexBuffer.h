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

    enum BufferUsage {
        STREAM_DRAW = 0x88E0,
        STREAM_READ = 0x88E1,
        STREAM_COPY = 0x88E2,
        STATIC_DRAW = 0x88E4,
        STATIC_READ = 0x88E5,
        STATIC_COPY = 0x88E6,
        DYNAMIC_DRAW = 0x88E8,
        DYNAMIC_READ = 0x88E9,
        DYNAMIC_COPY = 0x88EA
    };

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

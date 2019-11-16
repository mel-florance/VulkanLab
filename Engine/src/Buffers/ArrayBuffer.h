#ifndef VULKANLAB_ARRAY_BUFFER_H
#define VULKANLAB_ARRAY_BUFFER_H

#include <glad/glad.h>

class ArrayBuffer {
public:
    /**
     * ArrayBuffer constructor
     * Create a new array buffer.
     */
    ArrayBuffer() {
        glGenVertexArrays(1, &this->id);
    }

    /**
     * ArrayBuffer destructor
     * Delete the associated buffer.
     */
    ~ArrayBuffer() {
        glDeleteVertexArrays(1, &this->id);
    }

    /**
     * Bind the array buffer.
     */
    inline void bind() {
        glBindVertexArray(this->id);
    }

    /**
     * Unbind the array buffer.
     */
    static inline void unbind() {
        glBindVertexArray(0);
    }

    /**
     * Enable an attribute on the array buffer.
     * @param attr
     */
    static inline void enableAttribute(GLuint attr = 0) {
        glEnableVertexAttribArray(attr);
    }

    /**
     * Return the OpenGL id of the array buffer.
     * @return
     */
    inline unsigned int getId() {
        return id;
    }

private:
    unsigned int id;
};

#endif //VULKANLAB_ARRAY_BUFFER_H

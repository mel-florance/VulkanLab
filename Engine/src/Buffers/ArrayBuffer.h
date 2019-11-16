#ifndef VULKANLAB_ARRAY_BUFFER_H
#define VULKANLAB_ARRAY_BUFFER_H

class ArrayBuffer {
public:
    /**
     * ArrayBuffer constructor
     */
    ArrayBuffer() {

    }

    /**
     * ArrayBuffer destructor
     */
    ~ArrayBuffer() {

    }

    /*
     * Bind the buffer to the gpu.
     */
    inline void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, this->id);
    }

    /**
     * Enable a vertex attribute.
     */
     static inline void enableAttribute(GLuint attr = 0) {
        glEnableVertexAttribArray(attr);
     }

    /**
     * Return the OpenGL buffer id.
     * @return
     */
    inline unsigned int getId() const {
        return this->id;
    }

    /**
     * Set the OpenGL buffer id.
     * @param id
     */
    inline void setId(unsigned int id) {
        this->id = id;
    }

private:
    unsigned int id;
};

#endif //VULKANLAB_ARRAY_BUFFER_H

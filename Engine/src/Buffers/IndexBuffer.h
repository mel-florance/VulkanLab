#ifndef VULKANLAB_INDEXBUFFER_H
#define VULKANLAB_INDEXBUFFER_H

class IndexBuffer {
public:
    /**
     * The index buffer constructor.
     */
    IndexBuffer() {
        glGenBuffers(1, &this->id);
    }

    /**
     * The index buffer destructor.
     */
    ~IndexBuffer() {
    }

    inline void bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    }

    /**
     * Fill the buffer with data, size must the speficied.
     * @param data
     */
    inline void setData(void *data, GLsizei size) {
        this->data = data;
        this->bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /**
     * Return the OpenGL index buffer id.
     * @return
     */
    inline unsigned int getId() const {
        return id;
    }

    /**
     * Set the OpenGL index buffer id.
     * @param id
     */
    inline void setId(unsigned int id) {
        this->id = id;
    }

    /**
     * Return the OpenGL buffer data.
     * @return
     */
    inline void *getData() const {
        return data;
    }

private:
    unsigned int id;
    void* data;
};

#endif //VULKANLAB_INDEXBUFFER_H

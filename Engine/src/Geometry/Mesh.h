#ifndef VULKANLAB_MESH_H
#define VULKANLAB_MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh {
public:
    /**
     * Mesh constructor.
     */
    Mesh();

    /**
     * Mesh destructor.
     */
    ~Mesh();

    /*
     * Set the mesh vertices.
     */
    inline void setVertices(const std::vector<float>& verts) {
        this->vertices = verts;
        this->setVertexCount(verts.size() / 3);
    }

    /**
     * Return the mesh vertices.
     * @return
     */
    inline std::vector<float>& getVertices() {
        return this->vertices;
    }

    inline float getVerticesMemorySize() {
        return sizeof(&this->vertices[0]) * this->vertices.size();
    }

    /**
     * Set the vertex count of the mesh.
     */
    inline void setVertexCount(unsigned int count) {
        this->vertexCount = count;
    }

    /**
     * Draw the mesh.
     */
    inline void draw() {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

private:
    std::vector<float> vertices;
    unsigned int vertexCount;
};

#endif //VULKANLAB_MESH_H

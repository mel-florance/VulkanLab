#ifndef VULKANLAB_MESH_H
#define VULKANLAB_MESH_H

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
    inline void setVertices(std::vector<float> verts) {
        this->vertices = verts;
        this->setVertexCount(6);
    }

    /**
     * Return the mesh vertices.
     * @return
     */
    inline const std::vector<float> &getVertices() const {
        return this->vertices;
    }

    /**
     * Return the size in bytes of the vertices.
     */
    inline float getVerticesMemorySize() {
        return sizeof(&this->vertices[0]) * this->vertices.size();
    }

    /**
     * Return the mesh vertex count.
     */
    unsigned int getVertexCount() const {
        return this->vertexCount;
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
    void draw();

    /**
     * Return the mesh uvs array.
     * @return
     */
    const std::vector<float> &getUvs() const {
        return this->uvs;
    }

    /**
     * Set the mesh uvs array.
     * @param uvs
     */
    void setUvs(std::vector<float> uvs) {
        this->uvs = uvs;
    }

    /**
     * Return the size in bytes of the uvs.
     */
    inline float getUvsMemorySize() {
        return sizeof(&this->uvs[0]) * this->uvs.size();
    }

    /**
     * Return wireframe enabled.
     * @return
     */
    bool isWireframe() const {
        return this->wireframe;
    }

    /**
     * Set wireframe enabled.
     * @param wireframe
     */
    void setWireframe(bool wireframe) {
        this->wireframe = wireframe;
    }

private:
    std::vector<float> vertices;
    std::vector<float> uvs;
    unsigned int vertexCount;
    bool wireframe;
};

#endif //VULKANLAB_MESH_H

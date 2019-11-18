#ifndef VULKANLAB_MESH_H
#define VULKANLAB_MESH_H

#include <vector>
#include <unordered_map>

class ArrayBuffer;
class VertexBuffer;

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

    enum VertexBufferType {
        VERTEX,
        UV,
        NORMAL,
        TANGENT
    };

    enum DrawMode {
        POINTS = 0x0000,
        LINES = 0x0001,
        LINE_LOOP = 0x0002,
        LINE_STRIP = 0x0003,
        TRIANGLES = 0x0004,
        TRIANGLE_STRIP = 0x0005,
        TRIANGLE_FAN = 0x0006,
        QUADS = 0x0007
    };

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

    /**
     * Return the normals data array.
     * @return
     */
    inline const std::vector<float> &getNormals() const {
        return this->normals;
    }

    /**
     * Set the normals data array.
     * @param normals
     */
    inline void setNormals(const std::vector<float> &normals) {
        this->normals = normals;
    }

    /**
     * If the mesh array buffer is not a nullptr, then add the new buffer
     * to the list of mesh's buffers.
     * @param type
     * @param buffer
     */
    void addBuffer(VertexBufferType type, VertexBuffer* buffer);

private:
    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;

    ArrayBuffer* vao;
    std::unordered_map<VertexBufferType, VertexBuffer*> buffers;

    unsigned int vertexCount;
    bool wireframe;

    DrawMode drawMode;
};

#endif //VULKANLAB_MESH_H

#ifndef VULKANLAB_MESH_H
#define VULKANLAB_MESH_H

#include <map>
#include <vector>

class ArrayBuffer;

class VertexBuffer;

class Material;

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

    typedef std::map<ArrayBuffer *, std::vector<VertexBuffer *>> MeshBuffers;

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

    void setupBuffers();

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
    inline std::vector<float> &getVertices() {
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
    inline unsigned int getVertexCount() const {
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
    inline std::vector<float> &getUvs() {
        return this->uvs;
    }

    /**
     * Set the mesh uvs array.
     * @param uvs
     */
    inline void setUvs(std::vector<float> uvs) {
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
    inline std::vector<float> &getNormals() {
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
    void addBuffer(ArrayBuffer *vao, VertexBuffer *buffer);

    /**
     *
     * @param buffer
     */
    void addArrayBuffer(ArrayBuffer *buffer);

    /**
     * Return the mesh material.
     */
    inline Material *getMaterial() {
        return this->material;
    }

    /**
     * Set the mesh material.
     * @param material
     */
    inline void setMaterial(Material *material) {
        this->material = material;
    }

    /**
     * Check if a mesh has a material assigned.
     */
    inline bool hasMaterial() {
        return this->material != nullptr;
    }

    /**
     * Return the name of the mesh.
     */
    inline const char *getName() {
        return this->name;
    }

    /**
     * Set the name of the mesh.
     */
    inline void setName(const char *name) {
        this->name = name;
    }

    /**
     * Return the indices of the mesh.
     */
    inline std::vector<unsigned int> &getIndices() {
        return this->indices;
    }

    /**
     * Set the mesh indices.
     */
    inline void setMeshIndices(const std::vector<unsigned int> &indices) {
        this->indices = indices;
    }

    /**
     * Return the mesh tangents.
     */
    inline std::vector<float> &getTangents() {
        return this->tangents;
    }

    /*
     * Set the mesh tangents.
     */
    inline void setTangents(const std::vector<float> &tangents) {
        this->tangents = tangents;
    }

protected:
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;
    std::vector<float> tangents;

private:
    const char *name;
    MeshBuffers buffers;
    Material *material;

    unsigned int vertexCount;
    bool wireframe;

    DrawMode drawMode;
};

#endif //VULKANLAB_MESH_H

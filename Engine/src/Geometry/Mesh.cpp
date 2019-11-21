#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include "../Buffers/ArrayBuffer.h"
#include "../Buffers/VertexBuffer.h"

Mesh::Mesh() :
    vertices({}),
    uvs({}),
    normals({}),
    buffers({}),
    material(nullptr),
    vertexCount(0),
    wireframe(false),
    drawMode(TRIANGLES) {
}

Mesh::~Mesh() {

}

void Mesh::addBuffer(ArrayBuffer *vao, VertexBuffer *buffer) {

    auto it = this->buffers.find(vao);

    if (it != this->buffers.end())
        it->second.push_back(buffer);
}

void Mesh::draw() {
    if (this->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    MeshBuffers::iterator it = buffers.begin();

    for (; it != buffers.end(); ++it)
        it->first->bind();

    glDrawArrays(this->drawMode, 0, 6);
}

void Mesh::addArrayBuffer(ArrayBuffer *buffer) {
    this->buffers[buffer] = {};
}

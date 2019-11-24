#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include "../Buffers/ArrayBuffer.h"
#include "../Buffers/VertexBuffer.h"
#include "../Buffers/IndexBuffer.h"

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

    if (this->indices.size() > 0)
        glDrawElements(this->drawMode, this->indices.size(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(this->drawMode, 0, this->vertexCount);
}

void Mesh::addArrayBuffer(ArrayBuffer *buffer) {
    this->buffers[buffer] = {};
}

void Mesh::setupBuffers() {
    ArrayBuffer *vao = new ArrayBuffer();
    vao->bind();
    this->addArrayBuffer(vao);

    if (this->vertices.size() > 0) {
        VertexBuffer *vbo_position = new VertexBuffer();
        vbo_position->bind();
        vbo_position->setData(this->vertices.data(), this->vertices.size() * sizeof(float));

        // Create a position attribute for the vertices.
        VertexBuffer::AttributeData *position_attribute = new VertexBuffer::AttributeData();
        position_attribute->index = 0;
        position_attribute->size = 3;
        vbo_position->setAttribute(position_attribute);
        this->addBuffer(vao, vbo_position);
    }

    if (this->uvs.size() > 0) {
        // Create a vertex buffer for the uvs to be store.
        VertexBuffer *vbo_uvs = new VertexBuffer();
        vbo_uvs->bind();
        vbo_uvs->setData(this->uvs.data(), this->uvs.size() * sizeof(float));

        // Create a uv coordinate attribute for the uvs.
        VertexBuffer::AttributeData *texture_attribute = new VertexBuffer::AttributeData();
        texture_attribute->index = 1;
        texture_attribute->size = 2;
        vbo_uvs->setAttribute(texture_attribute);
        this->addBuffer(vao, vbo_uvs);
    }

    if (this->normals.size() > 0) {
        // Create a vertex buffer for the normals to be store.
        VertexBuffer *vbo_normals = new VertexBuffer();
        vbo_normals->bind();
        vbo_normals->setData(this->normals.data(), this->normals.size() * sizeof(float));

        // Create a normals attribute for the vao
        VertexBuffer::AttributeData *normals_attribute = new VertexBuffer::AttributeData();
        normals_attribute->index = 2;
        normals_attribute->size = 3;
        vbo_normals->setAttribute(normals_attribute);
        this->addBuffer(vao, vbo_normals);
    }

    if (this->indices.size() > 0) {
        // Create index buffer object.
        IndexBuffer* ibo = new IndexBuffer();
        ibo->setData(this->indices.data(), this->indices.size());
    }
}

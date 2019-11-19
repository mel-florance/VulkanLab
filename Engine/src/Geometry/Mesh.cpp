#include "Mesh.h"

#include <glad/glad.h>
#include "../Buffers/ArrayBuffer.h"

Mesh::Mesh() :
    wireframe(false),
    drawMode(TRIANGLES) {
}

Mesh::~Mesh() {

}

void Mesh::addBuffer(VertexBufferType type, VertexBuffer *buffer) {
    if (this->vao != nullptr) {
        this->vao->bind();
        this->buffers[type] = buffer;
    }
}

void Mesh::draw() {
    if (this->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawArrays(this->drawMode, 0, 6);
}

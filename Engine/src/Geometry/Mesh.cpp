#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh() :
        wireframe(false) {

}

Mesh::~Mesh() {

}

void Mesh::draw() {
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
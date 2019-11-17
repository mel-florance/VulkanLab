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

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
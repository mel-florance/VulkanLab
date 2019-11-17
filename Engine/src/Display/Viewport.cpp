#include <iostream>
#include <glad/glad.h>
#include "Viewport.h"

void Viewport::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::apply() {
    glViewport(position.x, position.y, size.x, size.y);
}

void Viewport::setColor(const glm::vec4 &color) {
    this->color = color;
    glClearColor(color.r, color.g, color.b, color.a);
}
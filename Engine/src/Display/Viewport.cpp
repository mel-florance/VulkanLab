#include <iostream>
#include <glad/glad.h>
#include "Viewport.h"
#include "Window.h"

Viewport::Viewport(Window *window) : window(window) {
    this->setColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
}

Viewport::~Viewport() {

}

void Viewport::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::apply() {
    size.x = Window::size.x;
    size.y = Window::size.y;
    glViewport(position.x, position.y, size.x, size.y);
}

void Viewport::setColor(const glm::vec4 &color) {
    this->color = color;
    glClearColor(color.r, color.g, color.b, color.a);
}

void Viewport::setWindow(Window *window) {
    this->window = window;
}
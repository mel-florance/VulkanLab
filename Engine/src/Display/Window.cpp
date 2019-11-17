#include <iostream>
#include <string>
#include <functional>
#include <glad/glad.h>
#include "Window.h"
#include "../Events/Event.h"

/**
 * Window constructor
 * @param size
 * @param title
 */
Window::Window(
    const glm::ivec2 &size,
    const std::string &title,
    const glm::vec2 &position
) :
    size(size),
    title(title),
    position(position),
    instance(nullptr) {

    if (glfwInit() == 0) {
        std::cout << "Can't init GLFW.";
    }

    this->instance = glfwCreateWindow(
        this->size.x,
        this->size.y,
        this->title.c_str(),
        nullptr,
        nullptr
    );

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    glfwMakeContextCurrent(this->instance);
    glfwSwapInterval(0);

    if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) {
        std::cout << "Can't init glad loader.";
    }

    Event<std::string, int> signal;

    signal.connect([](std::string arg1, int arg2) {
        std::cout << arg1 << " " << arg2 << std::endl;
    });

    signal.emit("The answer:", 42);
}

/**
 * Window update
 * @return
 */
void Window::update(std::function<void(glm::ivec2 &size)> callback) {
    while (!glfwWindowShouldClose(this->instance)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        callback(this->size);

        glfwSwapBuffers(this->instance);
        glfwPollEvents();
    }
}

/**
 * Window destructor
 */
Window::~Window() {
}
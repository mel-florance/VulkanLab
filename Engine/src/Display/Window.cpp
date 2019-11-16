#include <iostream>
#include <glad/glad.h>
#include "Window.h"


// Static initializers
glm::ivec2 Window::size = glm::ivec2(1280, 720);
glm::ivec2 Window::position = glm::ivec2(0, 0);

/**
 * Window constructor
 * @param size
 * @param title
 */
Window::Window(const std::string &title) : title(title), instance(nullptr) {

    int init_status = glfwInit();

    if (init_status == 0) {
        std::cout << "Can't init GLFW.";
    }

    this->instance = glfwCreateWindow(size.x, size.y, "Vulkan Lab", nullptr, nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    glfwMakeContextCurrent(this->instance);
    glfwSwapInterval(0);

    int glad_status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (glad_status == 0) {
        std::cout << "Can't init glad loader.";
    }

    glfwSetWindowSizeCallback(this->instance, &this->onResize);
}

void Window::onResize(GLFWwindow *window, int width, int height) {
    Window::size.x = width;
    Window::size.y = height;
}

/**
 * Window update
 * @return
 */
void Window::update(std::function<void(glm::ivec2 &size)> callback) {
    while (!glfwWindowShouldClose(this->instance)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        callback(Window::size);

        glfwSwapBuffers(this->instance);
        glfwPollEvents();
    }
}

/**
 * Window destructor
 */
Window::~Window() {
}
#include <iostream>
#include <string>
#include <functional>
#include <glad/glad.h>
#include "Window.h"
#include "../Events/Event.h"

/**
 * Window static initilizers
 */
glm::ivec2 Window::size = glm::ivec2(1280, 720);
std::string Window::title = "Vulkan Lab";
glm::vec2 Window::position = glm::vec2(0.0f);

/**
 * Window constructor
 * @param size
 * @param title
 */
Window::Window(
    const glm::ivec2 &size,
    const std::string &title,
    const glm::vec2 &position
) : instance(nullptr) {

    if (glfwInit() == 0) {
        std::cout << "Can't init GLFW.";
    }

    this->instance = glfwCreateWindow(
        Window::size.x,
        Window::size.y,
        Window::title.c_str(),
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

    glfwSetWindowSizeCallback(this->instance, &Window::onResize);
    glfwSetWindowCloseCallback(this->instance, &Window::onClose);
    glfwSetKeyCallback(this->instance, &Window::onKey);
    glfwSetCharCallback(this->instance, &Window::onChar);
    glfwSetMouseButtonCallback(this->instance, &Window::onMouseButton);
    glfwSetScrollCallback(this->instance, &Window::onScroll);
    glfwSetCursorPosCallback(this->instance, &Window::onMouseMove);
    glfwSetDropCallback(this->instance, &Window::onDrop);
}

/**
 * OnResize event - Triggered when the native window changes size.
 * @param window
 * @param width
 * @param height
 */
void Window::onResize(GLFWwindow *window, int width, int height) {
    Window::size = glm::ivec2(width, height);
}

/**
 * OnClose event - Triggered when the native window closes.
 * @param window
 */
void Window::onClose(GLFWwindow *window) {

}

/**
 * OnKey event - Triggered when a key action has ben done.
 * @param GLFWwindow* window
 * @param int width
 * @param int height
 */
void Window::onKey(GLFWwindow *window, int key, int scanCode, int action, int mods) {

}

/**
 * OnChar event - Triggered when a new input character happened.
 * @param GLFWwindow *window
 * @param unsigned int keyCode
 */
void Window::onChar(GLFWwindow *window, unsigned int keyCode) {

}

/**
 * OnMouseButton event - Triggered when a user input an action with the mouse buttons.
 * @param GLFWwindow *window
 * @param int button
 * @param int action
 * @param int mods
 */
void Window::onMouseButton(GLFWwindow *window, int button, int action, int mods) {

}

/**
 * OnScroll event - Triggered when a user scroll.
 * @param GLFWwindow *window
 * @param double x
 * @param double y
 */
void Window::onScroll(GLFWwindow *window, double x, double y) {

}

/**
 * OnMouseMove event - Triggered when the user moves the cursor.
 * @param GLFWwindow *window
 * @param double x
 * @param double y
 */
void Window::onMouseMove(GLFWwindow *window, double x, double y) {

}

/**
 * OnDrop event - Triggered when a user drop a file on the window.
 * It joins a list of file paths which were dropped.
 * @param GLFWwindow *window
 * @param int count
 * @param const char **paths
 */
void Window::onDrop(GLFWwindow *window, int count, const char **paths) {

}

/**
 * Window update
 * @param std::function callback
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


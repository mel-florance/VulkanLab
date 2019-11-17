#include <iostream>
#include <glad/glad.h>
#include "Window.h"

/**
 * Window static initializers
 */
glm::ivec2 Window::size = glm::ivec2(1280, 720);
glm::vec2 Window::position = glm::vec2(0.0f);
std::string Window::title = "Vulkan Lab";

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

    // Initialisation
    if (glfwInit() == 0) {
        std::cout << "Can't init GLFW.";
    }

    // Window creation
    instance = glfwCreateWindow(
        Window::size.x,
        Window::size.y,
        Window::title.c_str(),
        nullptr,
        nullptr
    );
    glfwMakeContextCurrent(instance);

    // Window options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);
    glfwSwapInterval(0);

    // Load glad to expose the OpenGL wrapper functions.
    if (gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) == 0) {
        std::cout << "Can't init glad loader.";
    }

    // Events mapping
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
 * OnResize event, called when the GLFW instance changes its dimensions.
 * @param GLFWwindow* - window
 * @param int - width
 * @param int - height
 */
void Window::onResize(GLFWwindow *window, int width, int height) {
    Window::size.x = width;
    Window::size.y = height;
}

/**
 * OnClose event, called when the GLFW instance closes.
 * @param GLFWwindow* - window
 */
void Window::onClose(GLFWwindow *window) {

}

/**
 * OnKey event, called when the GLFW instance get a new input from the keyboard.
 * @param GLFWwindow* - window
 * @param int - key
 * @param int - scan code
 * @param int - action
 * @param int - mods
 */
void Window::onKey(GLFWwindow *window, int key, int scanCode, int action, int mods) {

}

/**
 * OnChar event, called when the GLFW instance get a char input.
 * @param GLFWwindow* - window
 * @param int - key code
 */
void Window::onChar(GLFWwindow *window, unsigned int keyCode) {

}

/**
 * OnKey event, called when the GLFW instance get a char input.
 * @param GLFWwindow* - window
 * @param int - key code
 */
void Window::onMouseButton(GLFWwindow *window, int button, int action, int mods) {

}

/**
 * OnMouseMove event, called when the cusor of the mouse is moving.
 * @param GLFWwindow* window
 * @param double - x - The horizontal position of the mouse.
 * @param double - y - The vertical position of the mouse.
 */
void Window::onMouseMove(GLFWwindow *window, double x, double y) {

}

/**
 * OnDrop event, called when the user drag & drop an element on the window.
 * @param GLFWwindow* window - The native window instance.
 * @param int - count - The horizontal position of the mouse.
 * @param const char ** - paths - A list of paths of the dropped elements.
 */
void Window::onDrop(GLFWwindow *window, int count, const char **paths) {

}

/**
 * OnScroll event, called when the user uses the mouse wheel.
 * @param GLFWwindow* window - The native window instance.
 * @param double - x - The horizontal scroll on X axis.
 * @param double - y - The vertical scroll on Y axis.
 */
void Window::onScroll(GLFWwindow *window, double x, double y) {

}

/**
 * Window update function.
 * This function runs until a close event is sent to the native GLFW window.
 * @return void
 */
void Window::update(std::function<void(glm::ivec2 &size)> callback) {
    while (!glfwWindowShouldClose(instance)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        callback(size);

        glfwSwapBuffers(instance);
        glfwPollEvents();
    }
}

/**
 * Window destructor
 */
Window::~Window() {
}
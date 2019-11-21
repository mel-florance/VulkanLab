#include <iostream>
#include <string>
#include <functional>
#include <glad/glad.h>
#include "Window.h"
#include "../Core/Engine.h"
#include "../Events/Event.h"

/**
 * Window static initializers
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
    glfwSwapInterval(1);

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
 * OnResize event - Triggered when the native window changes size.
 * @param window
 * @param width
 * @param height
 */
void Window::onResize(GLFWwindow *window, int width, int height) {
    Window::size = glm::ivec2(width, height);
    WindowEvents data;
    data.width = width;
    data.height = height,
    Engine::onEvent(EventType::onWindowResize, &data);
}

/**
 * OnClose event - Triggered when the native window closes.
 * @param window
 */
void Window::onClose(GLFWwindow *window) {
    WindowEvents data;
    Engine::onEvent(EventType::onWindowClose, &data);
    Engine::stop();
}

/**
 * OnKey event - Triggered when a key action has ben done.
 * @param GLFWwindow* window
 * @param int width
 * @param int height
 */
void Window::onKey(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    KeyboardEvents data;
    data.key = key;
    data.scanCode = scanCode;
    data.keyAction = action;
    data.mods = mods;
    Engine::onEvent(EventType::onKeyboardInput, &data);
}

/**
 * OnChar event - Triggered when a new input character happened.
 * @param GLFWwindow *window
 * @param unsigned int keyCode
 */
void Window::onChar(GLFWwindow *window, unsigned int keyCode) {
    KeyboardEvents data;
    data.keyCode = keyCode;
    Engine::onEvent(EventType::onKeyboardChar, &data);
}

/**
 * OnMouseButton event - Triggered when a user input an action with the mouse buttons.
 * @param GLFWwindow *window
 * @param int button
 * @param int action
 * @param int mods
 */
void Window::onMouseButton(GLFWwindow *window, int button, int action, int mods) {
    MouseEvents data;
    data.button = button;
    data.action = action;
    data.mods = mods;
    Engine::onEvent(EventType::onMouseButton, &data);
}

/**
 * OnScroll event - Triggered when a user scroll.
 * @param GLFWwindow *window
 * @param double x
 * @param double y
 */
void Window::onScroll(GLFWwindow *window, double x, double y) {
    MouseEvents data;
    data.scroll.x = x;
    data.scroll.y = y;
    Engine::onEvent(EventType::onMouseScroll, &data);
}

/**
 * OnMouseMove event - Triggered when the user moves the cursor.
 * @param GLFWwindow *window
 * @param double x
 * @param double y
 */
void Window::onMouseMove(GLFWwindow *window, double x, double y) {
    MouseEvents data;
    data.position.x = x;
    data.position.y = y;
    Engine::onEvent(EventType::onMouseMove, &data);
}

/**
 * OnDrop event - Triggered when a user drop a file on the window.
 * It joins a list of file paths which were dropped.
 * @param GLFWwindow *window
 * @param int count
 * @param const char **paths
 */
void Window::onDrop(GLFWwindow *window, int count, const char **paths) {
    WindowEvents data;
    data.count = count;
    data.paths = paths;
    Engine::onEvent(EventType::onWindowDrop, &data);
}

/**
 * Window destructor
 */
Window::~Window() {
}

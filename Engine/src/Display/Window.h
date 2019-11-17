#ifndef VULKANLAB_WINDOW_H
#define VULKANLAB_WINDOW_H

#include <string>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Window {
public:
    Window(
        const glm::ivec2 &size = glm::ivec2(1280, 720),
        const std::string &title = "Vulkan Lab",
        const glm::vec2 &position = glm::vec2(0.0f)
    );

    ~Window();

    void update(std::function<void(glm::ivec2 &size)> callback);

    static void onResize(GLFWwindow *window, int width, int height);

    static void onClose(GLFWwindow *window);

    static void onKey(GLFWwindow *window, int key, int scanCode, int action, int mods);

    static void onChar(GLFWwindow *window, unsigned int keyCode);

    static void onMouseButton(GLFWwindow *window, int button, int action, int mods);

    static void onScroll(GLFWwindow *window, double x, double y);

    static void onMouseMove(GLFWwindow *window, double x, double y);

    static void onDrop(GLFWwindow *window, int count, const char **paths);

    inline GLFWwindow *getInstance() {
        return this->instance;
    }

    static glm::ivec2 size;
    static std::string title;
    static glm::vec2 position;
private:
    GLFWwindow *instance;
};

#endif //VULKANLAB_WINDOW_H
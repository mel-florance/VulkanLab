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
            const glm::vec2 &size = glm::vec2(1280, 720),
            const std::string &title = "Vulkan Lab",
            const glm::vec2 &position = glm::vec2(0.0f)
    );

    ~Window();

    void update(std::function<void(glm::vec2 &size)> callback);

private:
    glm::vec2 size;
    std::string title;
    glm::vec2 position;

    GLFWwindow *instance;
};

#endif //VULKANLAB_WINDOW_H

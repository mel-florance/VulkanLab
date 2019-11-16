#ifndef VULKANLAB_WINDOW_H
#define VULKANLAB_WINDOW_H

#include <string>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Window {
public:
    /**
     * Window constructor.
     * @param size
     * @param title
     * @param position
     */
    Window(const std::string &title = "Vulkan Lab");

    /**
     * Window destructor.
     */
    ~Window();

    /**
     * Update the window.
     */
    void update(std::function<void(glm::ivec2 &size)> callback);

    /**
     * Return the size of the window.
     */
    static inline glm::ivec2 &getSize() {
        return size;
    }

    /**
     * Return the title of the window.
     * @return
     */
    inline std::string &getTitle() {
        return title;
    }

    /**
     * Return the position of the window.
     */
    static inline glm::ivec2 &getPosition() {
        return position;
    }

    /**
     * Return the pointer to the native window.
     */
    inline GLFWwindow *getInstance() {
        return instance;
    }

    /**
     * Resize window event
     * @param width
     * @param height
     */
    static void onResize(GLFWwindow* window, int width, int height);

    static glm::ivec2 size;
    static glm::ivec2 position;
private:
    std::string title;
    GLFWwindow *instance;
};

#endif //VULKANLAB_WINDOW_H

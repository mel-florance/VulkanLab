#ifndef VULKANLAB_CLOCK_H
#define VULKANLAB_CLOCK_H

#include <GLFW/glfw3.h>

class Clock {
public:
    Clock() {}
    ~Clock() {}

    /**
     * Return the time in milliseconds from the GLFW get time function.
     * - TODO Improve it with a more precise timer.
     * @return
     */
    inline double getTime() {
        return time = glfwGetTime();
    }

private:
    double time;
};

#endif //VULKANLAB_CLOCK_H

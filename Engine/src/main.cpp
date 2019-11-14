#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Window.h"

int main() {
    Window *window = new Window();

    window->update([](glm::vec2 &size) {

    });

    delete window;

    return 0;
}

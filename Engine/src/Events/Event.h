#ifndef VULKANLAB_EVENT_H
#define VULKANLAB_EVENT_H

#include <glm/glm.hpp>

enum EventType {
    onMouseButton,
    onMouseMove,
    onMouseScroll,
    onKeyboardInput,
    onKeyboardChar,
    onWindowResize,
    onWindowDrop,
    onWindowClose,
    onWindowCursorEnter
};

struct Event {};

class MouseEvents : public Event {
public:
    MouseEvents() :
        position(glm::vec2(0.0f)),
        scroll(glm::vec2(0.0f)),
        button(0),
        action(0),
        mods(0) {}

    virtual ~MouseEvents() {}
    virtual void onMouseButton(Event *data) {}
    virtual void onMouseMove(Event *data) {}
    virtual void onMouseScroll(Event *data) {}

    glm::vec2 position;
    glm::vec2 scroll;
    int button;
    int action;
    int mods;
};

class KeyboardEvents : public Event {
public:
    KeyboardEvents() :
        key(0),
        scanCode(0),
        keyAction(0),
        mods(0),
        keyCode(0) {}

    virtual ~KeyboardEvents() {}
    virtual void onKeyboardInput(Event *data) {}
    virtual void onKeyboardChar(Event *data) {}

    int key;
    int scanCode;
    int keyAction;
    int mods;
    unsigned int keyCode;
};

class WindowEvents : public Event {
public:
    WindowEvents() :
        width(0),
        height(0),
        count(0),
        paths(nullptr) {}

    virtual ~WindowEvents() {}
    virtual void onWindowResize(Event *data) {}
    virtual void onWindowDrop(Event *data) {}
    virtual void onWindowClose(Event *data) {}
    virtual void onWindowCursorEnter(Event *data) {}

    int width;
    int height;
    int count;
    const char **paths;
};

#endif //VULKANLAB_EVENT_H

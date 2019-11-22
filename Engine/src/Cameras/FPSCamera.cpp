#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

#include "FPSCamera.h"
#include "../Display/Window.h"
#include "../Display/Viewport.h"

FPSCamera::FPSCamera(Viewport *viewport) :
    Camera(viewport),
    delta(0.0f),
    yaw(90.0f),
    pitch(0.0f),
    roll(0.0f),
    friction(10.0f),
    sensitivity(0.3f),
    mouseOffset(glm::vec2(0.0f)),
    lastPosition(glm::vec2(0.0f)),
    isFirstTimeMoving(false),
    constrainAxis(true),
    velocity(glm::vec3(0.0f)),
    speed(125.0f),
    speedMultiplier(10.0f),
    minSpeed(0.1f),
    maxSpeed(1000.0f){
//    glfwSetCursorPos(this->viewport->getWindow()->getInstance(), 0.5, 0.5);
}

FPSCamera::~FPSCamera() {

}

void FPSCamera::compute() {
    float alpha = glm::radians(this->pitch);
    float beta = cosf(alpha);
    float theta = glm::radians(this->yaw);

    this->direction = glm::normalize(glm::vec3(
        cos(theta) * beta,
        sin(alpha) * 1.0f,
        sin(theta) * beta
    ));

    this->right = glm::normalize(glm::cross(this->direction, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->direction));
}

void FPSCamera::update(float delta) {
    glfwSetInputMode(this->viewport->getWindow()->getInstance(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    this->delta = delta;
    float dts = this->delta * this->speed;

    glm::vec3 z = this->direction * dts;
    glm::vec3 y = this->up * dts;
    glm::vec3 x = this->right * dts;

    if (movementDirection & Direction::FORWARD)
        this->velocity += z;
    if (movementDirection & Direction::BACKWARD)
        this->velocity -= z;
    if (movementDirection & Direction::LEFT)
        this->velocity -= x;
    if (movementDirection & Direction::RIGHT)
        this->velocity += x;
    if (movementDirection & Direction::UP)
        this->velocity -= y;
    if (movementDirection & Direction::DOWN)
        this->velocity += y;

    this->compute();

    this->projection = glm::perspective(
        this->fov,
        this->aspectRatio,
        this->getNear(),
        this->getFar()
    );

    this->velocity *= 1.0f / (1.0f + this->delta * this->friction);
    Camera::position += this->velocity * this->delta;

    this->view = glm::lookAt(
        Camera::position,
        Camera::position + direction,
        Camera::up
    );

//    std::cout << glm::to_string(this->view) << std::endl;
}

void FPSCamera::onMouseMove(Event *data) {
    MouseEvents *event = (MouseEvents *) data;

    if (this->isFirstTimeMoving) {
        this->lastPosition = event->position;
        this->isFirstTimeMoving = false;
    }

    this->mouseOffset = event->position - this->lastPosition;
    this->lastPosition = event->position;

    this->yaw += this->mouseOffset.x * this->sensitivity;
    this->pitch -= this->mouseOffset.y * this->sensitivity;

    if (this->constrainAxis) {
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }
}

void FPSCamera::onMouseButton(Event *data) {
    MouseEvents *event = (MouseEvents *) data;

    if (event->action == GLFW_PRESS)
        std::cout << event->button << std::endl;
}

void FPSCamera::onKeyboardInput(Event *data) {
    KeyboardEvents *event = (KeyboardEvents *) data;
    bool release = event->keyAction == GLFW_RELEASE;

    switch (event->key) {
        case GLFW_KEY_W:
            release
            ? movementDirection &= ~(Direction::FORWARD)
            : movementDirection |= Direction::FORWARD;
            break;
        case GLFW_KEY_S:
            release
            ? movementDirection &= ~(Direction::BACKWARD)
            : movementDirection |= Direction::BACKWARD;
            break;
        case GLFW_KEY_A:
            release
            ? movementDirection &= ~(Direction::LEFT)
            : movementDirection |= Direction::LEFT;
            break;
        case GLFW_KEY_D:
            release
            ? movementDirection &= ~(Direction::RIGHT)
            : movementDirection |= Direction::RIGHT;
            break;
        case GLFW_KEY_Q:
            release
            ? movementDirection &= ~(Direction::UP)
            : movementDirection |= Direction::UP;
            break;
        case GLFW_KEY_E:
            release
            ? movementDirection &= ~(Direction::DOWN)
            : movementDirection |= Direction::DOWN;
            break;
    }
}

void FPSCamera::onMouseScroll(Event *data) {
    MouseEvents *event = (MouseEvents *) data;

    this->speed += event->scroll.y / 10.0f * this->speedMultiplier;

    if (this->speed < this->minSpeed)
        this->speed = this->minSpeed;

    if (this->speed > this->maxSpeed)
        this->speed = this->maxSpeed;
}

void FPSCamera::onWindowResize(Event *data) {
    WindowEvents *event = (WindowEvents *) data;
    this->aspectRatio = event->width / event->height;
    std::cout << this->aspectRatio << std::endl;
}

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

#include "FPSCamera.h"
#include "../Display/Window.h"
#include "../Display/Viewport.h"

FPSCamera::FPSCamera(Viewport *viewport) :
    Camera(viewport),
    yaw(90.0f),
    pitch(0.0f),
    roll(0.0f),
    velocity(glm::vec3(0.0f)),
    speed(125.0f),
    delta(0.0f),

    friction(10.0f),
    sensitivity(0.3f),
    mouseOffset(glm::vec2(0.0f)),
    lastPosition(glm::vec2(0.0f)),
    isFirstTimeMoving(false),
    constrainAxis(true) {
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
    this->delta = delta;
}

void FPSCamera::onMouseMove(Event *data) {
    MouseEvents *e = (MouseEvents *) data;

    if (this->isFirstTimeMoving) {
        this->lastPosition = e->position;
        this->isFirstTimeMoving = false;
    }

    this->mouseOffset = e->position - this->lastPosition;
    this->lastPosition = e->position;

    this->yaw -= this->mouseOffset.x * this->sensitivity;
    this->pitch -= this->mouseOffset.y * this->sensitivity;

    if (this->constrainAxis) {
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }

    this->compute();

    this->projection = glm::perspective(
        this->fov,
        this->aspectRatio,
        this->getNear(),
        this->getFar()
    );

    this->velocity *= 1.0f / (1.0f + this->delta * this->friction);
    this->position += this->velocity * this->delta;

    this->view = glm::lookAt(
        this->position,
        this->position + direction,
        this->up
    );

    std::cout << glm::to_string(this->position) << std::endl;
}

void FPSCamera::onMouseButton(Event *data) {
    MouseEvents *e = (MouseEvents *) data;

    if (e->action == GLFW_PRESS)
        std::cout << e->button << std::endl;
}

void FPSCamera::onKeyboardInput(Event *data) {
    GLFWwindow *native = (GLFWwindow *) getViewport()->getWindow()->getInstance();

    if (glfwGetKey(native, GLFW_KEY_W) == GLFW_PRESS)
        this->velocity += this->direction * this->delta * this->speed;
    if (glfwGetKey(native, GLFW_KEY_S) == GLFW_PRESS)
        this->velocity -= this->direction * this->delta * this->speed;
    if (glfwGetKey(native, GLFW_KEY_A) == GLFW_PRESS)
        this->velocity += this->right * this->delta * this->speed;
    if (glfwGetKey(native, GLFW_KEY_D) == GLFW_PRESS)
        this->velocity -= this->right * this->delta * this->speed;
    if (glfwGetKey(native, GLFW_KEY_Q) == GLFW_PRESS)
        this->velocity -= this->up * this->delta * this->speed;
    if (glfwGetKey(native, GLFW_KEY_E) == GLFW_PRESS)
        this->velocity += this->up * this->delta * this->speed;
}

void FPSCamera::onMouseScroll(Event *data) {
//    MouseEvents *e = (MouseEvents *) data;
}

void FPSCamera::onWindowResize(Event *data) {
    WindowEvents *e = (WindowEvents *) data;
    this->aspectRatio = e->width / e->height;
}

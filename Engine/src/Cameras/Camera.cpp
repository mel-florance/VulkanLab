#include "Camera.h"

Camera::Camera(Viewport *viewport) :
    projection(glm::mat4(1.0f)),
    position(glm::vec3(0.0f)),
    direction(glm::vec3(0.0f)),
    up(glm::vec3(0.0f)),
    right(glm::vec3(0.0f)),
    viewport(viewport) {
}

Camera::~Camera() {

}
#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "../Display/Viewport.h"

Camera::Camera(Viewport *viewport) :
    direction(glm::vec3(0.0f, 0.0f, -1.0f)),
    right(glm::vec3(0.0f)),
    up(glm::vec3(0.0f)),
    fov(70.0f),
    aspectRatio(viewport->getWidth() / viewport->getHeight()),
    clipping(glm::vec2(0.01f, 1000.0f)),
    projection(glm::mat4(1.0f)),
    position(glm::vec3(0.0f)),
    viewport(viewport) {
}

Camera::~Camera() {

}
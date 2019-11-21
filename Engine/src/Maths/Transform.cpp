#include "Transform.h"

glm::mat4 Transform::getMatrix() {
    glm::mat4 translation = glm::translate(this->position);
    glm::mat4 rotationX = glm::rotate(this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotationY = glm::rotate(this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationZ = glm::rotate(this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaling = glm::scale(this->scale);

    glm::mat4 final_rotation = rotationZ * rotationY * rotationX;
    return translation * final_rotation * scaling;
}
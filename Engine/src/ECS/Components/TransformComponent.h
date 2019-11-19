#ifndef VULKANLAB_TRANSFORM_COMPONENT_H
#define VULKANLAB_TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct Transform {
    ECS_DECLARE_TYPE;

    Transform(
            const glm::vec3& position = glm::vec3(0.0f),
            const glm::vec3& rotation = glm::vec3(0.0f),
            const glm::vec3& scale = glm::vec3(1.0f),
            const glm::mat4& matrix = glm::mat4(1.0f)
        ) :
        position(position),
        rotation(rotation),
        scale(scale),
        matrix(matrix)
    {}

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 matrix;
    bool isDirty;
};

ECS_DEFINE_TYPE(Position);

#endif //VULKANLAB_TRANSFORM_COMPONENT_H

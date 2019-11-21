#ifndef VULKANLAB_TRANSFORM_COMPONENT_H
#define VULKANLAB_TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include "../../Maths/Transform.h"

struct TransformComponent {
    ECS_DECLARE_TYPE;

    TransformComponent() : transform(new Transform()){}

    Transform* transform;
};

ECS_DEFINE_TYPE(TransformComponent);

#endif //VULKANLAB_TRANSFORM_COMPONENT_H

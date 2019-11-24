#ifndef VULKANLAB_TRANSFORM_COMPONENT_H
#define VULKANLAB_TRANSFORM_COMPONENT_H

#include <glm/glm.hpp>
#include "../ECS.h"

ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include <memory>
#include "../../Maths/Transform.h"

struct TransformComponent {
    ECS_DECLARE_TYPE;

    TransformComponent() {
        transform = std::make_shared<Transform>();
    }

    ~TransformComponent() {

    }

    std::shared_ptr<Transform> transform;
};

ECS_DEFINE_TYPE(TransformComponent);

#endif //VULKANLAB_TRANSFORM_COMPONENT_H

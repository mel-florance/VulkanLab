#ifndef VULKANLAB_ROTATION_COMPONENT_H
#define VULKANLAB_ROTATION_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct Rotation {
    ECS_DECLARE_TYPE;

    Rotation(float angle) : angle(angle) {}

    Rotation() {}

    float angle;
};

ECS_DEFINE_TYPE(Rotation);

#endif //VULKANLAB_ROTATION_COMPONENT_H

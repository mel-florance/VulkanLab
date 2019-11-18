#ifndef VULKANLAB_POSITION_COMPONENT_H
#define VULKANLAB_POSITION_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct Position {
    ECS_DECLARE_TYPE;

    Position(float x, float y) : x(x), y(y) {}

    Position() {}

    float x;
    float y;
};

ECS_DEFINE_TYPE(Position);

#endif //VULKANLAB_POSITION_COMPONENT_H

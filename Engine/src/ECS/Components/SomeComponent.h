#ifndef VULKANLAB_SOME_COMPONENT_H
#define VULKANLAB_SOME_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct SomeComponent {
    ECS_DECLARE_TYPE;
    SomeComponent() {}
};

ECS_DEFINE_TYPE(SomeComponent);

#endif //VULKANLAB_SOME_COMPONENT_H

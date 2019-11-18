#ifndef VULKANLAB_SOME_EVENT_H
#define VULKANLAB_SOME_EVENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct SomeEvent {
    ECS_DECLARE_TYPE;

    int num;
};

ECS_DEFINE_TYPE(SomeEvent);

#endif //VULKANLAB_SOME_EVENT_H

#ifndef VULKANLAB_NODE_COMPONENT_H
#define VULKANLAB_NODE_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include "../../Scene/Node.h"

struct NodeComponent {
    ECS_DECLARE_TYPE;
    NodeComponent() {}

    Node* node;
};

ECS_DEFINE_TYPE(NodeComponent);

#endif //VULKANLAB_NODE_COMPONENT_H

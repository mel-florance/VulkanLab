#ifndef VULKANLAB_MESH_COMPONENT_H
#define VULKANLAB_MESH_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

struct MeshComponent {
    ECS_DECLARE_TYPE;
    MeshComponent() {}

    Mesh* mesh;
};

ECS_DEFINE_TYPE(MeshComponent);


#endif //VULKANLAB_MESH_COMPONENT_H

#ifndef VULKANLAB_MATERIAL_COMPONENT_H
#define VULKANLAB_MATERIAL_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include <memory>
#include "../../Materials/Material.h"

struct MaterialComponent {
    ECS_DECLARE_TYPE;
    MaterialComponent(const char* name) :
        name(name),
        material(std::make_shared<Material>(name))
    {}

    const char* name;
    std::shared_ptr<Material> material;
};

ECS_DEFINE_TYPE(MaterialComponent);

#endif //VULKANLAB_MATERIAL_COMPONENT_H

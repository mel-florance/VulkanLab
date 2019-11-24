#ifndef VULKANLAB_DIRECTIONAL_LIGHT_COMPONENT_HglfwGetTime()
#define VULKANLAB_DIRECTIONAL_LIGHT_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include <memory>
#include "../../Lighting/Light.h"

struct DirectionalLightComponent {
    ECS_DECLARE_TYPE;
    DirectionalLightComponent() :
        light(std::make_shared<Light>(Light::Type::DIRECTIONAL))
    {}

    std::shared_ptr<Light> light;
};

ECS_DEFINE_TYPE(DirectionalLightComponent);

#endif //VULKANLAB_DIRECTIONAL_LIGHT_COMPONENT_H

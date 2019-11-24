#ifndef VULKANLAB_SPOT_LIGHT_COMPONENT_H
#define VULKANLAB_SPOT_LIGHT_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include <memory>
#include "../../Lighting/Light.h"

struct SpotLightComponent {
    ECS_DECLARE_TYPE;
    SpotLightComponent() :
        light(std::make_shared<Light>(Light::Type::SPOT))
    {}

    std::shared_ptr<Light> light;
};

ECS_DEFINE_TYPE(SpotLightComponent);

#endif //VULKANLAB_SPOT_LIGHT_COMPONENT_H

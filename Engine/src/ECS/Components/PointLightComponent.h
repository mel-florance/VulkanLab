#ifndef VULKANLAB_POINT_LIGHT_COMPONENT_H
#define VULKANLAB_POINT_LIGHT_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include "../../Lighting/Light.h"

struct PointLightComponent {
    ECS_DECLARE_TYPE;
    PointLightComponent() :
        light(std::make_shared<Light>(Light::Type::POINT))
    {
        light->setIntensity(3.0f);
        light->setPosition(glm::vec3(-2.0f, -4.0f, 3.0f));
        light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

        light->setConstant(1.0f);
        light->setLinear(0.09f);
        light->setQuadratic(0.032f);
    }

    std::shared_ptr<Light> light;
};

ECS_DEFINE_TYPE(PointLightComponent);

#endif //VULKANLAB_POINT_LIGHT_COMPONENT_H

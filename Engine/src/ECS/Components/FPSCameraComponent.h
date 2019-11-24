#ifndef VULKANLAB_FPS_CAMERA_COMPONENT_H
#define VULKANLAB_FPS_CAMERA_COMPONENT_H

#include "../ECS.h"
ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

#include "../../Display/Viewport.h"
#include "../../Cameras/FPSCamera.h"

struct FPSCameraComponent {
    ECS_DECLARE_TYPE;
    FPSCameraComponent(Viewport* viewport) :
        viewport(viewport),
        camera(std::make_shared<FPSCamera>(viewport))
    {}

    Viewport* viewport;
    std::shared_ptr<FPSCamera> camera;
};

ECS_DEFINE_TYPE(FPSCameraComponent);

#endif //VULKANLAB_FPS_CAMERA_COMPONENT_H

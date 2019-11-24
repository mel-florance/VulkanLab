#include "Renderer.h"
#include "../Display/Viewport.h"
#include "../Core/Engine.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Geometry/Mesh.h"
#include "../Materials/Material.h"
#include "../Shaders/Shader.h"
#include "../Cameras/Camera.h"

#include "../ECS/Components/MeshComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/NodeComponent.h"
#include "../ECS/Components/PointLightComponent.h"

Renderer::Renderer(Engine *engine) : engine(engine) {
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glEnable(GL_CULL_FACE);
}

Renderer::~Renderer() {
}

void Renderer::render() {
    auto viewport = this->engine->getViewport();
    viewport->apply();
    viewport->clear();

    Scene *scene = this->engine->getScenesManager()->getActiveScene();

    scene->getWorld()->each<TransformComponent, MeshComponent>([&](
        Entity *entity,
        ComponentHandle<TransformComponent> transformComponent,
        ComponentHandle<MeshComponent> meshComponent
        ) {

        if (meshComponent->mesh != nullptr) {
            auto material = meshComponent->mesh->getMaterial();
            auto camera = scene->getActiveCamera();

            if (material != nullptr) {
                auto shader = material->getShader();

                if (shader != nullptr) {
                    shader->bind();

                    shader->setUniformMat4f("projection", camera->getProjection());
                    shader->setUniformMat4f("view", camera->getView());
                    shader->setUniformMat4f("transform", transformComponent->transform->getMatrix());
                    shader->setUniform3f("camPos", camera->getPosition());

                    unsigned int lightIndex = 0;

                    scene->getWorld()->each<PointLightComponent>([&](
                        Entity *entity,
                        ComponentHandle<PointLightComponent> pointLightComponent
                    ) {
                        auto light = pointLightComponent->light;
                        auto index_str = std::to_string(lightIndex);

                        if (light != nullptr) {
                            // TODO: Make a light parameter struct to handle this better ?
                            // This probably needs to be cached as well to avoid some useless rebinding if
                            // it hasn't changed.
                            shader->setUniform1i("lights[" + index_str + "].type", light->getType());
                            shader->setUniform1f("lights[" + index_str + "].intensity", light->getIntensity());
                            shader->setUniform3f("lights[" + index_str + "].color", light->getColor());
                            shader->setUniform3f("lights[" + index_str + "].position", light->getPosition());
                            shader->setUniform1f("lights[" + index_str + "].constant", light->getConstant());
                            shader->setUniform1f("lights[" + index_str + "].linear", light->getLinear());
                            shader->setUniform1f("lights[" + index_str + "].quadratic", light->getQuadratic());
                            shader->setUniform1f("lights[" + index_str + "].innerCutoff", light->getInnerCutoff());
                            shader->setUniform1f("lights[" + index_str + "].outerCutoff", light->getOuterCutoff());

                            ++lightIndex;
                        }
                    });

                    meshComponent->mesh->draw();
                }
            }
        }
    });
}
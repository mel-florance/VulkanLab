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

Renderer::Renderer(Engine *engine) : engine(engine) {
}

Renderer::~Renderer() {

}

void Renderer::render() {
    auto viewport = this->engine->getViewport();
    viewport->apply();
    viewport->clear();

    Scene *scene = this->engine->getScenesManager()->getActiveScene();

    scene->getWorld()->each<MeshComponent, TransformComponent>([&](
        Entity *entity,
        ComponentHandle<MeshComponent> meshComponent,
        ComponentHandle<TransformComponent> transformComponent) {
        auto material = meshComponent->mesh->getMaterial();

        if (material != nullptr) {
            material->getShader()->bind();
            material->getShader()->setUniformMat4f("projection", scene->getActiveCamera()->getProjection());
            material->getShader()->setUniformMat4f("view", scene->getActiveCamera()->getView());
            material->getShader()->setUniformMat4f("transform", transformComponent->transform->getMatrix());
            meshComponent->mesh->draw();
        }
    });
}
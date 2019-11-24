#include "Scene.h"

ECS_TYPE_IMPLEMENTATION;

Scene::Scene() :
    activeCamera(nullptr),
    defaultShader(nullptr)
{
    this->createWorld();
}

void Scene::createWorld() {
    this->world = World::createWorld();
}

Scene::~Scene() {
    delete this->world;
}
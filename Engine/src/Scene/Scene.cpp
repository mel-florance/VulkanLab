#include "Scene.h"

ECS_TYPE_IMPLEMENTATION;

Scene::Scene() {
    this->createWorld();
}

void Scene::createWorld() {
    this->world = World::createWorld();
}

Scene::~Scene() {
    delete this->world;
}
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : activeScene(nullptr) {

}

SceneManager::~SceneManager() {

}

void SceneManager::addScene(Scene* scene) {
    this->scenes.emplace_back(scene);
    this->activeScene = scene;
}

void SceneManager::setScenes(const ScenesList& scenes) {
    this->scenes = scenes;
}

bool SceneManager::removeScene(Scene* scene) {
    auto it = std::find(this->scenes.begin(), this->scenes.end(), scene);

    if (it != this->scenes.end()) {
        this->scenes.erase(it);
        return true;
    }
    else
        return false;
}

Scene *SceneManager::getActiveScene() {
    return this->activeScene;
}

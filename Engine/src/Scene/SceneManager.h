#ifndef VULKANLAB_SCENE_MANAGER_H
#define VULKANLAB_SCENE_MANAGER_H

#include <vector>
#include <memory>
#include <algorithm>

class Scene;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    typedef std::vector<Scene*> ScenesList;

    /**
     * Add a new scene to the list.
     * @param scene
     */
    void addScene(Scene* scene);

    /**
     * Return the scenes list.
     */
    inline const ScenesList& getScenes() {
        return this->scenes;
    }

    /**
     * The the scenes list.
     * @param scenes
     */
    void setScenes(const ScenesList& scenes);

    /**
     * Remove a scene from the list by pointer.
     * @param scene
     * @return
     */
    bool removeScene(Scene* scene);

private:
    ScenesList scenes;
};

#endif //VULKANLAB_SCENE_MANAGER_H

#ifndef VULKANLAB_SCENE_H
#define VULKANLAB_SCENE_H

#include "../ECS/ECS.h"
using namespace ECS;

class Camera;
class Shader;

class Scene {
public:
    Scene();
    ~Scene();

    /**
     * Create a new world.
     */
    void createWorld();

    /**
     * Destroy the world.
     */
     inline void destroyWorld() {
         if (this->world != nullptr)
            this->world->destroyWorld();
     }

    /**
     * Register a system to the ECS world.
     * @tparam T
     * @param system
     * @return
     */
    template<typename T>
    inline T* registerSystem() {
        T* instance = new T();
        this->world->registerSystem(instance);
        return instance;
    }

    /**
     * Enable a previously added system.
     */
    inline void enableSystem(EntitySystem* system) {
        this->world->enableSystem(system);
    }

    /**
     * Disable a previously added system.
     * @param system
     */
    inline void disableSystem(EntitySystem* system) {
        this->world->disableSystem(system);
    }

    /**
     * Create a new entity in the world.
     * @return
     */
    inline Entity* createEntity() {
        return this->world->create();
    }

    /**
     * Destroy an entity
     */
     inline void destroyEntity(Entity* entity, bool immediate = false) {
         this->world->destroy(entity, immediate);
     }

    /**
     * Return the scene world.
     * @return
     */
    inline World *getWorld() const {
        return this->world;
    }

    /**
     * Set the scene world.
     * @param world
     */
    inline void setWorld(World *world) {
        this->world = world;
    }

    /**
     * Cleanup the world entities.
     */
    inline void cleanupWorld() {
        this->world->cleanup();
    }

    /**
     * Emit a world event
     * @tparam - T - EventType
     * @tparam - Args - The list of argument to pass.
     */
    template<typename T, typename ...Args>
    inline void emit(Args... args) {
        this->world->emit<T>(std::forward<Args>(args)...);
    }

    /**
     * Update the scene and the associated world.
     * TODO: At which interval the tick is updated ?
     */
    inline void update(float delta = 16.0f) {
        this->world->tick(delta);
    }

    /**
     * Return the number of entities in the world.
     * @return
     */
    inline unsigned int getEntitiesCount() {
        return this->world->getCount();
    }

    /**
     * Return the active camera.
     * @return
     */
    inline Camera *getActiveCamera() const {
        return this->activeCamera;
    }

    /*
     * Set the active camera.
     */
    inline void setActiveCamera(Camera *activeCamera) {
        this->activeCamera = activeCamera;
    }


    inline Shader *getDefaultShader() {
        return this->defaultShader;
    }

    inline void setDefaultShader(Shader *defaultShader) {
        this->defaultShader = defaultShader;
    }

private:
    World* world;
    Camera* activeCamera;
    Shader* defaultShader;

};

#endif //VULKANLAB_SCENE_H

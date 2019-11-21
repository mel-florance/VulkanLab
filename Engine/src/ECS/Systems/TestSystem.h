#ifndef VULKANLAB_TEST_SYSTEM_H
#define VULKANLAB_TEST_SYSTEM_H

#include <iostream>
#include "../ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/MeshComponent.h"
#include "../Components/NodeComponent.h"
#include "../Events/SomeEvent.h"

ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

class TestSystem :
    public EntitySystem,
    public EventSubscriber<Events::OnEntityCreated>,
    public EventSubscriber<Events::OnEntityDestroyed>,
    public EventSubscriber<Events::OnComponentRemoved<TransformComponent>>,
    public EventSubscriber<SomeEvent> {
public:
    virtual ~TestSystem() {}

    virtual void configure(class World *world) override {
        world->subscribe<Events::OnEntityCreated>(this);
        world->subscribe<Events::OnEntityDestroyed>(this);
        world->subscribe<Events::OnComponentRemoved<TransformComponent>>(this);
        world->subscribe<SomeEvent>(this);
    }

    virtual void unconfigure(class World *world) override {
        world->unsubscribeAll(this);
    }

    virtual void tick(class World *world, float deltaTime) override {
        world->each<TransformComponent>([&](Entity *ent, ComponentHandle<TransformComponent> transform) -> void {
//            transform->position.x += deltaTime;
        });
    }

    virtual void receive(class World *world, const Events::OnEntityCreated &event) override {
        std::cout << "An entity was created!" << std::endl;
    }

    virtual void receive(class World *world, const Events::OnEntityDestroyed &event) override {
        std::cout << "An entity was destroyed!" << std::endl;
    }

    virtual void receive(class World *world, const Events::OnComponentRemoved<TransformComponent> &event) override {
        std::cout << "A position component was removed!" << std::endl;
    }

    virtual void receive(class World *world, const SomeEvent &event) override {
        std::cout << "I received SomeEvent with value " << event.num << "!" << std::endl;

        // Let's delete an entity while iterating because why not?
        world->all([&](Entity *ent) {
            if ((int)ent->getEntityId() + 1 == event.num)
                world->destroy(world->getById(event.num));

            if ((int)ent->getEntityId() == event.num)
                std::cout << "Woah, we shouldn't get here!" << std::endl;
        });
    }
};

#endif //VULKANLAB_TEST_SYSTEM_H

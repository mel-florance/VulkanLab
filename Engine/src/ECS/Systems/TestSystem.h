#ifndef VULKANLAB_TEST_SYSTEM_H
#define VULKANLAB_TEST_SYSTEM_H

#include <iostream>
#include "../ECS.h"
#include "../Components/PositionComponent.h"
#include "../Components/RotationComponent.h"
#include "../Components/SomeComponent.h"
#include "../Events/SomeEvent.h"

ECS_TYPE_IMPLEMENTATION;
using namespace ECS;

class TestSystem :
    public EntitySystem,
    public EventSubscriber<Events::OnEntityCreated>,
    public EventSubscriber<Events::OnEntityDestroyed>,
    public EventSubscriber<Events::OnComponentRemoved<Position>>,
    public EventSubscriber<Events::OnComponentRemoved<Rotation>>,
    public EventSubscriber<SomeEvent> {
public:
    virtual ~TestSystem() {}

    virtual void configure(class World *world) override {
        world->subscribe<Events::OnEntityCreated>(this);
        world->subscribe<Events::OnEntityDestroyed>(this);
        world->subscribe<Events::OnComponentRemoved<Position>>(this);
        world->subscribe<Events::OnComponentRemoved<Rotation>>(this);
        world->subscribe<SomeEvent>(this);
    }

    virtual void unconfigure(class World *world) override {
        world->unsubscribeAll(this);
    }

    virtual void tick(class World *world, float deltaTime) override {
        world->each<Position, Rotation>([&](Entity *ent, ComponentHandle<Position> pos, ComponentHandle<Rotation> rot) -> void {
            pos->x += deltaTime;
            pos->y += deltaTime;
            rot->angle += deltaTime * 2;
        });
    }

    virtual void receive(class World *world, const Events::OnEntityCreated &event) override {
        std::cout << "An entity was created!" << std::endl;
    }

    virtual void receive(class World *world, const Events::OnEntityDestroyed &event) override {
        std::cout << "An entity was destroyed!" << std::endl;
    }

    virtual void receive(class World *world, const Events::OnComponentRemoved<Position> &event) override {
        std::cout << "A position component was removed!" << std::endl;
    }

    virtual void receive(class World *world, const Events::OnComponentRemoved<Rotation> &event) override {
        std::cout << "A rotation component was removed!" << std::endl;
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

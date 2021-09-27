#include "EntityManager.h"

#include <QDebug>

#include "Components/Base/EntityInfo.h"
#include "Components/Base/Transform.h"
#include "Components/Base/Camera.h"
#include "Components/Primitive/Triangle.h"
#include "Components/Primitive/Cube.h"
#include "Components/Primitive/Quad.h"

namespace render{

Entity* EntityManager::root_ = nullptr;

Entity* EntityManager::createEntity(QString entityId, QString name, Entity* parent){
    if(!root_ || !root_->valid()){
        root_ = new Entity(entityId,name);
        return root_;
    }

    auto entity = new Entity(entityId,name);
    if(parent == nullptr){
        entity->parent_ = root_;
        root_->addChild(entity);
    }else{
        entity->parent_ = parent;
        parent->addChild(entity);
    }
    return entity;
}

void EntityManager::deleteEntity(Entity* entity){
    if(entity->parent_)
        entity->parent_->removeChild(entity);
    delete entity;
}

Entity* EntityManager::root(){
    return root_;
}

bool EntityManager::addComponentWithType(Entity *entity, render::ComponentType type) {
    switch(type){
        case render::ComponentType::kTriangle:
            entity->addComponent<render::Triangle>();
            break;
        case render::ComponentType::kQuad:
            entity->addComponent<render::Quad>();
            break;
        case render::ComponentType::kCube:
            entity->addComponent<render::Cube>();
            break;
        case render::ComponentType::kTransform:
            entity->addComponent<render::Transform>();
            break;
        case render::ComponentType::kCamera:
            entity->addComponent<render::Camera>();
            break;
        default:
            assert(false);
    }
    return true;
}

bool EntityManager::removeComponentWithType(Entity *entity, render::ComponentType type) {
    switch(type){
        case render::ComponentType::kTriangle:
            entity->removeComponent<render::Triangle>();
            break;
        case render::ComponentType::kQuad:
            entity->removeComponent<render::Quad>();
            break;
        case render::ComponentType::kCube:
            entity->removeComponent<render::Cube>();
            break;
        case render::ComponentType::kTransform:
            entity->removeComponent<render::Transform>();
            break;
        case render::ComponentType::kCamera:
            entity->removeComponent<render::Camera>();
            break;
        default:
            assert(false);
    }
    return true;
}

std::vector<render::Component *> EntityManager::allComponents(Entity *entity) {
    //TODO 这里需要注册所有的component
    auto com = ENTT::registry.try_get<
            render::EntityInfo,
            render::Transform,
            render::Camera,
            render::Triangle,
            render::Cube,
            render::Quad>(entity->entity_);

    std::vector<render::Component*> components;
    allComponentsGetter(components,com);

    return components;
}
}
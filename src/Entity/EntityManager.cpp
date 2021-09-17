#include "EntityManager.h"

#include <QDebug>

#include "Components/Base/EntityInfo.h"
#include "Components/Primitive/Triangle.h"
#include <Components/Primitive/Quad.h>

CFEntity* EntityManager::root_ = nullptr;

CFEntity* EntityManager::createEntity(QString entityId, QString name, CFEntity* parent){
    if(!root_ || !root_->valid()){
        root_ = new CFEntity(entityId,name);
        return root_;
    }

    auto entity = new CFEntity(entityId,name);
    if(parent == nullptr){
        entity->parent_ = root_;
        root_->addChild(entity);
    }else{
        entity->parent_ = parent;
        parent->addChild(entity);
    }
    return entity;
}

void EntityManager::deleteEntity(CFEntity* entity){
    if(entity->parent_)
        entity->parent_->removeChild(entity);
    delete entity;
}

CFEntity* EntityManager::root(){
    return root_;
}

bool EntityManager::addComponentWithType(CFEntity *entity, CFEngineRender::ComponentType type) {
    switch(type){
        case CFEngineRender::ComponentType::kTriangle:
            entity->addComponent<CFEngineRender::Triangle>();
            break;
        case CFEngineRender::ComponentType::kQuad:
            entity->addComponent<CFEngineRender::Quad>();
            break;
        default:
            assert(false);
    }
    return true;
}

std::vector<CFEngineRender::Component *> EntityManager::allComponents(CFEntity *entity) {
    //TODO 这里需要注册所有的component
    auto com = ENTT::registry.try_get<
            CFEngineRender::EntityInfo,
            CFEngineRender::Triangle,
            CFEngineRender::Quad>(entity->entity_);

    std::vector<CFEngineRender::Component*> components;
    allComponentsGetter(components,com);

    return components;
}

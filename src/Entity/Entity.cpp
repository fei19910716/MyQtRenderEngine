//
// Created by fordchen on 2021/9/13.
//


#include "Entity.h"
#include "Components/Base/EntityInfo.h"

namespace render{
Entity::Entity() {

}

Entity::Entity(const Entity &other){

}

Entity::Entity(QString entityId, QString name){
    entity_ = ENTT::registry.create();
    ENTT::registry.emplace<render::EntityInfo>(entity_,entityId,name);
}

Entity::~Entity() noexcept {
    for(auto& item: children_){
        ENTT::registry.destroy(item->entity_);
    }
    ENTT::registry.destroy(entity_);
}

bool Entity::valid(){
    return ENTT::registry.valid(entity_);
}

void Entity::addChild(Entity* child){
    if(std::find(children_.begin(),children_.end(),child) == children_.end()){
        children_.push_back(child);
    }
}

void Entity::removeChild(Entity* child){
    for(auto ite = children_.begin(); ite !=children_.end(); ite++){
        if(*ite == child){
            children_.erase(ite);
            return;
        }
    }
}

}

//
// Created by fordchen on 2021/9/13.
//

#include "CFEntity.h"

#include "Components/Base/MetaInfo.h"
#include "Components/Primitive/Triangle.h"

CFEntity::CFEntity() {

}

CFEntity::CFEntity(const CFEntity &other){

}

CFEntity::CFEntity(QString entityId, QString name){
    entity_ = ENTT::registry.create();
    ENTT::registry.emplace<MetaInfo>(entity_,entityId,name);
}

CFEntity::~CFEntity() noexcept {
    for(auto& item: children_){
        ENTT::registry.destroy(item->entity_);
    }
    ENTT::registry.destroy(entity_);
}

bool CFEntity::valid(){
    return ENTT::registry.valid(entity_);
}

void CFEntity::addChild(CFEntity* child){
    if(std::find(children_.begin(),children_.end(),child) == children_.end()){
        children_.push_back(child);
    }
}

void CFEntity::removeChild(CFEntity* child){
    for(auto ite = children_.begin(); ite !=children_.end(); ite++){
        if(*ite == child){
            children_.erase(ite);
            return;
        }
    }
}

std::vector<Component*> CFEntity::allComponents(){
    auto com = ENTT::registry.try_get<MetaInfo,Triangle>(entity_); //TODO 这里需要注册所有的component
    std::vector<Component*> components;
    allComponentsGetter(components,com);
    return components;
}
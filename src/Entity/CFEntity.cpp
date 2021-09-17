//
// Created by fordchen on 2021/9/13.
//


#include "CFEntity.h"
#include "Components/Base/EntityInfo.h"

CFEntity::CFEntity() {

}

CFEntity::CFEntity(const CFEntity &other){

}

CFEntity::CFEntity(QString entityId, QString name){
    entity_ = ENTT::registry.create();
    ENTT::registry.emplace<CFEngineRender::EntityInfo>(entity_,entityId,name);
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

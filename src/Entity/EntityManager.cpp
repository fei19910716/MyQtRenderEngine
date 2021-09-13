#include "EntityManager.h"

#include <QDebug>


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

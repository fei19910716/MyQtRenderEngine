#include "EntityManager.h"

#include <QDebug>

#include "Components/Primitive/Triangle.h"
#include "Components/Base/MetaInfo.h"

CFEntity EntityManager::root_;
entt::registry EntityManager::m_registry;
std::vector<CFEntity> EntityManager::children;

EntityManager::EntityManager(){

}

void EntityManager::createEntity(int id){
    qDebug() << "add entity----";
    root_ = m_registry.create();
    std::vector<MetaInfo> childs = {
        {"001","one",{}},
        {"002","two",{}}
    };
    m_registry.emplace<MetaInfo>(root_,"001","Triangle",std::move(childs));
    m_registry.emplace<Triangle>(root_);
}

void EntityManager::deleteEntity(int id){
    qDebug() << "del entity----";
    m_registry.destroy(root_);
}

CFEntity& EntityManager::getRoot(){
    return root_;
}

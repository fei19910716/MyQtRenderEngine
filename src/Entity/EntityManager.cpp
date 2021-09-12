#include "EntityManager.h"

#include <QDebug>

#include "Components/Primitive/Triangle.h"
#include "Components/Base/MetaInfo.h"

CFEntity EntityManager::root_;

CFEntity EntityManager::createEntity(QString entityId, QString name, CFEntity* parent){
    if(!ENTT::registry.valid(root_)){
        root_ = ENTT::registry.create();
        ENTT::registry.emplace<MetaInfo>(root_,entityId,name,std::vector<MetaInfo>());
        return root_;
    }
    CFEntity entity = ENTT::registry.create();

    ENTT::registry.emplace<MetaInfo>(entity,entityId,name,std::vector<MetaInfo>{});
    
    return entity;
}

void EntityManager::deleteEntity(QString entityId){
    auto view = ENTT::registry.view<const MetaInfo>();
    view.each([&](const auto entity, const MetaInfo &metaInfo) { 
        if(metaInfo.entityId() == entityId){
            ENTT::registry.destroy(entity);
        }
     });
}

CFEntity& EntityManager::getRoot(){
    return root_;
}

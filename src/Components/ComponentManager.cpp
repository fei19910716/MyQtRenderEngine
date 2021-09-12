//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"

#include "Base/component.h"
#include "Primitive/Triangle.h"
#include "Base/MetaInfo.h"

std::vector<ComponentDescription*> ComponentManager::allComponentDescriptions_;

void ComponentManager::registerComponentDescriptions() {
    ComponentDescription* triangle = new ComponentDescription;
    triangle->type_ = ComponentType::kTriangle;
    triangle->label_ = QObject::tr("Triangle");
    triangle->group_ = ComponentGroup::kPrimitive;

    allComponentDescriptions_.emplace_back(triangle);
}

std::vector<ComponentDescription*> ComponentManager::getComponentDescriptions(){
    return allComponentDescriptions_;
}

std::vector<Component*>  ComponentManager::getComponentsOfEntity(CFEntity& entity){
    auto com = ENTT::registry.try_get<MetaInfo,Triangle>(entity); //TODO 这里需要注册所有的component

    std::vector<Component*> coms;

    coms.push_back(new Triangle(001,1));

    coms.push_back(new Triangle(002,1));

    return coms;
}

template<typename T>
bool ComponentManager::addComponentOfEntity(CFEntity& entity){
    auto com = ENTT::registry.try_get<T>(entity);
    if(com == nullptr){
        ENTT::registry.emplace<T>(entity);
        return true;
    }else{
        assert(false);
        return false;
    }
}

template<typename T>
T* ComponentManager::getComponentOfEntity(CFEntity& entity){
    auto com = ENTT::registry.try_get<T>(entity);
    if(com == nullptr){
        return com;
    } else{
        return nullptr;
    }
}

template<typename T>
void deleteComponentOfEntity(CFEntity& entity){
    ENTT::registry.remove<T>(entity);
}

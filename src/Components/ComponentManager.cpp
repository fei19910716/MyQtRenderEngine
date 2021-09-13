//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"

#include "Base/cfcomponent.h"

std::unordered_map<ComponentType,ComponentDescription*> ComponentManager::allComponentDescriptions_;

void ComponentManager::registerComponentDescriptions() {
    ComponentDescription* componentDescription_ = new ComponentDescription;
    componentDescription_->type_ = ComponentType::kTriangle;
    componentDescription_->group_ = ComponentGroup::kPrimitive;
    componentDescription_->isHiddenInList_ = false;

    auto pair = std::make_pair<ComponentType,ComponentDescription*>(ComponentType::kTriangle,componentDescription_);
    allComponentDescriptions_.insert(pair);
}

std::vector<ComponentDescription*>& ComponentManager::componentDescriptions(){
    
    return allComponentDescriptions_;
}

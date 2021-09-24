//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"
#include "Components/Primitive/Triangle.h"
#include "Components/Primitive/Quad.h"

namespace render{

std::unordered_map<ComponentType,std::shared_ptr<ComponentDescription>> ComponentManager::allComponentDescriptions_;

void ComponentManager::registerComponentDescriptions() {

    REGISTER_COMPONENT_DESCRIPTION(Triangle)

    REGISTER_COMPONENT_DESCRIPTION(Quad)
}

std::shared_ptr<ComponentDescription> ComponentManager::componentDescriptionWithType(ComponentType type){
    return allComponentDescriptions_[type];
}

std::unordered_map<ComponentType,std::shared_ptr<ComponentDescription>>& ComponentManager::componentDescriptions(){
    
    return allComponentDescriptions_;
}

}

//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"
#include "Components/Primitive/Triangle.h"
#include "Components/Primitive/Quad.h"


std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>> CFEngineRender::ComponentManager::allComponentDescriptions_;

void CFEngineRender::ComponentManager::registerComponentDescriptions() {

    REGISTER_COMPONENT_DESCRIPTION(Triangle)

    REGISTER_COMPONENT_DESCRIPTION(Quad)
}

std::shared_ptr<CFEngineRender::ComponentDescription> CFEngineRender::ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType type){
    return allComponentDescriptions_[type];
}

std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>>& CFEngineRender::ComponentManager::componentDescriptions(){
    
    return allComponentDescriptions_;
}

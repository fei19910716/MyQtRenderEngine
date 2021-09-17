//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"
#include "Components/Primitive/Triangle.h"
#include "Components/Primitive/Quad.h"

std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>> CFEngineRender::ComponentManager::allComponentDescriptions_;

void CFEngineRender::ComponentManager::registerComponentDescriptions() {

    auto triangle = std::make_pair(ComponentType::kTriangle,CFEngineRender::Triangle::MakeComponentDescription());
    allComponentDescriptions_.insert(triangle);


    auto quad = std::make_pair(ComponentType::kQuad,CFEngineRender::Triangle::MakeComponentDescription());
    allComponentDescriptions_.insert(quad);
}

std::shared_ptr<CFEngineRender::ComponentDescription> CFEngineRender::ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType type){
    return allComponentDescriptions_[type];
}

std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>>& CFEngineRender::ComponentManager::componentDescriptions(){
    
    return allComponentDescriptions_;
}

//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"

std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>> CFEngineRender::ComponentManager::allComponentDescriptions_;

void CFEngineRender::ComponentManager::registerComponentDescriptions() {
    auto componentDescription_ = std::make_shared<CFEngineRender::ComponentDescription>();
    componentDescription_->type_ = ComponentType::kTriangle;
    componentDescription_->group_ = ComponentGroup::kPrimitive;
    componentDescription_->label_ = "Triangle";
    componentDescription_->isHiddenInList_ = false;

    auto pair = std::make_pair(ComponentType::kTriangle,componentDescription_);
    allComponentDescriptions_.insert(pair);
}

std::shared_ptr<CFEngineRender::ComponentDescription> CFEngineRender::ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType type){
    return allComponentDescriptions_[type];
}

std::unordered_map<CFEngineRender::ComponentType,std::shared_ptr<CFEngineRender::ComponentDescription>>& CFEngineRender::ComponentManager::componentDescriptions(){
    
    return allComponentDescriptions_;
}

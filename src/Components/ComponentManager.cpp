//
// Created by fordchen on 2021/8/31.
//

#include "ComponentManager.h"

#include "Base/component.h"

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

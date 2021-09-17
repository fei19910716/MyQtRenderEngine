//
// Created by fordchen on 2021/9/14.
//

#include "UIComponent.h"

CFEngineRender::UIComponent::~UIComponent() noexcept {

}

CFEngineRender::UIComponent::UIComponent() {
    this->MakeComponentPropertyDescriptions();
}

CFEngineRender::UIComponent::UIComponent(int componentId, int entityId):Component(componentId,entityId){
    this->MakeComponentPropertyDescriptions();
}
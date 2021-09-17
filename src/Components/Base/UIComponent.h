//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_UICOMPONENT_H
#define CFRENDERENGINE_UICOMPONENT_H

#include <memory>
#include "Component.h"

CFENGINE_RENDER_START

#define REGISTER_COMPONENT_DESCRIPTION(ClassName)\
componentDescription_ = ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType::k##ClassName);

#define ADD_COMPONENT_PROPERTY_DESCRIPTION(...)\


class UIComponent: public Component {
    Q_OBJECT
public:
    COMPONENT_PROPERTY(std::vector<std::shared_ptr<ComponentPropertyDescription>>, PropertyDescriptions, propertyDescriptions, {})
    COMPONENT_PROPERTY(std::shared_ptr<ComponentDescription>, ComponentDescription, componentDescription, nullptr)

    UIComponent() = default;
    UIComponent(int componentId, int entityId):Component(componentId,entityId){}

    virtual ~UIComponent();

    virtual void MakeComponentPropertyDescriptions() = 0;

};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_UICOMPONENT_H

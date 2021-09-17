//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_UICOMPONENT_H
#define CFRENDERENGINE_UICOMPONENT_H

#include <memory>
#include "Component.h"

CFENGINE_RENDER_START

class UIComponent: public Component {
    Q_OBJECT
    Q_PROPERTY(std::vector<std::shared_ptr<ComponentPropertyDescription>> propertyDescriptions READ propertyDescriptions WRITE setPropertyDescriptions)
    Q_PROPERTY(std::shared_ptr<ComponentDescription> componentDescription READ componentDescription WRITE setComponentDescription)
public:
    UIComponent() = default;
    UIComponent(int componentId, int entityId):Component(componentId,entityId){}

    virtual ~UIComponent();

    virtual void MakeComponentPropertyDescriptions() = 0;


    std::vector<std::shared_ptr<ComponentPropertyDescription>> propertyDescriptions_;
    std::shared_ptr<ComponentDescription> componentDescription_;

public:

    std::shared_ptr<ComponentDescription> componentDescription() const
    {
        return componentDescription_;
    }
    void setComponentDescription(std::shared_ptr<ComponentDescription> componentDescription)
    {
        componentDescription_ = componentDescription;
    }

    std::vector<std::shared_ptr<ComponentPropertyDescription>> propertyDescriptions() const
    {
        return propertyDescriptions_;
    }
    void setPropertyDescriptions(std::vector<std::shared_ptr<ComponentPropertyDescription>> propertyDescriptions)
    {
        propertyDescriptions_ = propertyDescriptions;
    }
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_UICOMPONENT_H

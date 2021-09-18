#pragma once

#include <QColor>

#include <vector>

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"

CFENGINE_RENDER_START

class Triangle: public UIComponent{
    Q_OBJECT
public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)


    COMPONENT_PROPERTY(QString, Name, name, "Triangle")
    COMPONENT_PROPERTY(QColor, Color, color, QColor(255, 0, 0, 127))
    COMPONENT_PROPERTY(Priority, Priority, priority, Priority::Low)

    Triangle():UIComponent(){
        REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Triangle)
    }
    Triangle(int componentId, int entityId):UIComponent(componentId,entityId){
        REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Triangle)
    }

    static std::shared_ptr<ComponentDescription> MakeComponentDescription(){
        auto triangle_ = std::make_shared<ComponentDescription>();
        triangle_->type_ = ComponentType::kTriangle;
        triangle_->group_ = ComponentGroup::kPrimitive;
        triangle_->label_ = "Triangle";
        triangle_->isHiddenInList_ = false;

        return triangle_;
    }

    void MakeComponentPropertyDescriptions() override{
        // 
        ComponentPropertyDescription* name = new ComponentPropertyDescription;
        name->name_ = "name";
        name->label_ = "name";
        name->type_ = ComponentPropertyType::kString;
        name->editable_ = false;

        ComponentPropertyDescription* priority = new ComponentPropertyDescription;
        priority->name_ = "priority";
        priority->label_ = "priority";
        priority->type_ = ComponentPropertyType::kEnum;
        priority->enums_ = {"High","Low","VeryHigh","VeryLow"};

        ComponentPropertyDescription* color = new ComponentPropertyDescription;
        color->name_ = "color";
        color->label_ = "color";
        color->type_ = ComponentPropertyType::kColor;

        ComponentPropertyDescription* enable = new ComponentPropertyDescription;
        enable->name_ = "enable";
        enable->label_ = "enable";
        enable->type_ = ComponentPropertyType::kBool;

        ADD_COMPONENT_PROPERTY_DESCRIPTION(name,priority,color,enable)
    }


    std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,  // first Triangle
    };

signals:
};
CFENGINE_RENDER_END
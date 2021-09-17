#pragma once

#include <QColor>

#include <vector>

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"

CFENGINE_RENDER_START

class Triangle: public UIComponent{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QColor color READ color)
    Q_PROPERTY(Priority priority READ priority)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    Triangle(){
        this->MakeComponentPropertyDescriptions();

        componentDescription_ = ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType::kTriangle);
        
    }
    Triangle(int componentId, int entityId):UIComponent(componentId,entityId){
        this->MakeComponentPropertyDescriptions();

        componentDescription_ = ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType::kTriangle);
    }

    ~Triangle() = default;

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

        this->propertyDescriptions_.emplace_back(name);
        this->propertyDescriptions_.emplace_back(priority);
        this->propertyDescriptions_.emplace_back(color);
        this->propertyDescriptions_.emplace_back(enable);
    }


    std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,  // first Triangle
    };

public:

    QString name_ = "Triangle";
    QString name(){
        return name_;
    }


    QColor color_ = QColor(255, 0, 0, 127);
    QColor color(){
        return color_;
    }

    Priority priority_ = Priority::Low;
    Priority priority(){
        return priority_;
    }

signals:
};
CFENGINE_RENDER_END
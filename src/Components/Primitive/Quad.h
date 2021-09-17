#pragma once

#include <QColor>

#include <vector>

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"

CFENGINE_RENDER_START

class Quad: public UIComponent{
Q_OBJECT
public:

    COMPONENT_PROPERTY(QString, Name, name, "Quad")
    COMPONENT_PROPERTY(QColor, Color, color, QColor(255, 0, 0, 127))

    Quad(){
        this->MakeComponentPropertyDescriptions();

        componentDescription_ = ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType::kQuad);

    }
    Quad(int componentId, int entityId):UIComponent(componentId,entityId){
        this->MakeComponentPropertyDescriptions();

        componentDescription_ = ComponentManager::componentDescriptionWithType(CFEngineRender::ComponentType::kQuad);
    }

    ~Quad() = default;

    static std::shared_ptr<ComponentDescription> MakeComponentDescription(){
        auto quad_ = std::make_shared<CFEngineRender::ComponentDescription>();
        quad_->type_ = ComponentType::kQuad;
        quad_->group_ = ComponentGroup::kPrimitive;
        quad_->label_ = "Quad";
        quad_->isHiddenInList_ = false;

        return quad_;
    }

    void MakeComponentPropertyDescriptions() override{
        //
        ComponentPropertyDescription* name = new ComponentPropertyDescription;
        name->name_ = "name";
        name->label_ = "name";
        name->type_ = ComponentPropertyType::kString;
        name->editable_ = false;

        ComponentPropertyDescription* color = new ComponentPropertyDescription;
        color->name_ = "color";
        color->label_ = "color";
        color->type_ = ComponentPropertyType::kColor;

        ComponentPropertyDescription* enable = new ComponentPropertyDescription;
        enable->name_ = "enable";
        enable->label_ = "enable";
        enable->type_ = ComponentPropertyType::kBool;

        ADD_COMPONENT_PROPERTY_DESCRIPTION(name,color,enable)
    }


    std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    std::vector<unsigned int> indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

signals:
};
CFENGINE_RENDER_END

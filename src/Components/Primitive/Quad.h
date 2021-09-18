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

    Quad():UIComponent(){
        REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Quad)

    }
    Quad(int componentId, int entityId):UIComponent(componentId,entityId){
        REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Quad)
    }

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
        auto name = new ComponentPropertyDescription("name","name");
        name->type_ = ComponentPropertyType::kString;
        name->editable_ = false;

        auto color = new ComponentPropertyDescription("color","color");
        color->type_ = ComponentPropertyType::kColor;

        auto enable = new ComponentPropertyDescription("enable","enable");
        enable->type_ = ComponentPropertyType::kBool;

        ADD_COMPONENT_PROPERTY_DESCRIPTION(name,color,enable)
    }


    std::vector<float> vertices = {
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,     // top left
    };

    std::vector<unsigned int> indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

signals:
};
CFENGINE_RENDER_END

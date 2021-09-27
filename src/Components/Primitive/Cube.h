#pragma once

#include <QColor>

#include <vector>

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"

namespace render{

    class Cube: public UIComponent{
    Q_OBJECT
    public:

        COMPONENT_PROPERTY(QColor, Color, color, QColor(255, 0, 0, 127))

        Cube():UIComponent(){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Cube)
        }
        Cube(int componentId, int entityId):UIComponent(componentId,entityId){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Cube)
        }

        static std::shared_ptr<ComponentDescription> MakeComponentDescription(){
            auto cube = std::make_shared<ComponentDescription>();
            cube->type_ = ComponentType::kCube;
            cube->group_ = ComponentGroup::kPrimitive;
            cube->label_ = "Cube";
            cube->isHiddenInList_ = false;

            return cube;
        }

        void MakeComponentPropertyDescriptions() override{

            ComponentPropertyDescription* color = new ComponentPropertyDescription("color","color");
            color->type_ = ComponentPropertyType::kColor;

            ComponentPropertyDescription* enable = new ComponentPropertyDescription("enable","enable");
            enable->type_ = ComponentPropertyType::kBool;

            ADD_COMPONENT_PROPERTY_DESCRIPTION(color,enable)
        }

        std::vector<float> vertices = {
                0.5f,  0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,

                -1.0, -1.0,  1.0,
                1.0, -1.0,  1.0,
                -1.0,  1.0,  1.0,
                1.0,  1.0,  1.0,
                -1.0, -1.0, -1.0,
                1.0, -1.0, -1.0,
                -1.0,  1.0, -1.0,
                1.0,  1.0, -1.0,
        };

        std::vector<unsigned int> indices = {
                0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
        };

    };
}
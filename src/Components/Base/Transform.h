#pragma once

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"
#include "Core/glm.h"

namespace render{
    class Transform: public UIComponent
    {
    Q_OBJECT
    public:

        COMPONENT_PROPERTY(glm::vec3, Position, position, glm::vec3(0.0,0.0,0.0))
        COMPONENT_PROPERTY(glm::vec3, Rotation, rotation, glm::vec3(0.0,0.0,0.0))
        COMPONENT_PROPERTY(glm::vec3, Scale, scale, glm::vec3(1.0,1.0,1.0))

    public:
        Transform():UIComponent(){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Transform)
        }
        Transform(int componentId, int entityId):UIComponent(componentId,entityId){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Transform)
        }

        static std::shared_ptr<ComponentDescription> MakeComponentDescription(){
            auto transform_ = std::make_shared<ComponentDescription>();
            transform_->type_ = ComponentType::kTransform;
            transform_->group_ = ComponentGroup::kPrimitive;
            transform_->label_ = "Transform";
            transform_->isHiddenInList_ = false;

            return transform_;
        }

        void MakeComponentPropertyDescriptions() override{
            //
            ComponentPropertyDescription* position = new ComponentPropertyDescription("position","position");
            position->type_ = ComponentPropertyType::kVec3;

            ComponentPropertyDescription* rotation = new ComponentPropertyDescription("rotation","rotation");
            rotation->type_ = ComponentPropertyType::kVec3;

            ComponentPropertyDescription* scale = new ComponentPropertyDescription("scale","scale");
            scale->type_ = ComponentPropertyType::kVec3;

            ADD_COMPONENT_PROPERTY_DESCRIPTION(position,rotation,scale)
        }
    };

}

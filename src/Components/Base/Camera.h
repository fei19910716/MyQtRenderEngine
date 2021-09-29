#pragma once

#include "Components/Base/UIComponent.h"
#include "Components/ComponentManager.h"
#include "Core/glm.h"

#undef near
#undef far

namespace render{
    class Camera: public UIComponent
    {
    Q_OBJECT
    public:

        COMPONENT_PROPERTY(float, Fov, fov, 45)
        COMPONENT_PROPERTY(float, Aspect, aspect, 1.0)
        COMPONENT_PROPERTY(float, Near, near, 0.1)
        COMPONENT_PROPERTY(float, Far, far, 100.0)

        COMPONENT_PROPERTY(glm::vec2, Delta,delta,glm::vec2(0.0f,0.0f))
    public:
        Camera():UIComponent(){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Camera)
        }
        Camera(int componentId, int entityId):UIComponent(componentId,entityId){
            REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(Camera)
        }

        static std::shared_ptr<ComponentDescription> MakeComponentDescription(){
            auto camera = std::make_shared<ComponentDescription>();
            camera->type_ = ComponentType::kCamera;
            camera->group_ = ComponentGroup::kBase;
            camera->label_ = "Camera";
            camera->isHiddenInList_ = false;

            return camera;
        }

        void MakeComponentPropertyDescriptions() override{
            //
            ComponentPropertyDescription* fov = new ComponentPropertyDescription("fov","fov");
            fov->type_ = ComponentPropertyType::kFloat;

            ComponentPropertyDescription* aspect = new ComponentPropertyDescription("aspect","aspect");
            aspect->type_ = ComponentPropertyType::kFloat;

            ComponentPropertyDescription* near = new ComponentPropertyDescription("near","near");
            near->type_ = ComponentPropertyType::kFloat;

            ComponentPropertyDescription* far = new ComponentPropertyDescription("far","far");
            far->type_ = ComponentPropertyType::kFloat;

            ADD_COMPONENT_PROPERTY_DESCRIPTION(fov,aspect,near,far)
        }
    };

}

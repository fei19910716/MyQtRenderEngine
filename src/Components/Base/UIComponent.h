//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_UICOMPONENT_H
#define CFRENDERENGINE_UICOMPONENT_H

#include <memory>
#include <iostream>
#include "Component.h"

namespace render{

#define REGISTER_COMPONENT_AND_PROPERTY_DESCRIPTION(ClassName)\
componentDescription_ = ComponentManager::componentDescriptionWithType(render::ComponentType::k##ClassName); \
this->MakeComponentPropertyDescriptions();

#define ARG_COUNTX(...)  A1X(__VA_ARGS__)
#define A3X(x) x
#define A1X(...) A3X(A4X(__VA_ARGS__, 4, 3, 2, 1, 0))
#define A4X(_1_, _2_, _3_, _4_, count, ...) count
 
#define PREPARE_MACRO(x)     x
#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)
 
#define TOSTRING(x)         #x //转为字符串返回
 
#define DO_ARG_WORK(x)	{								\
    this->propertyDescriptions_.emplace_back(x);\
}
 
#define Do_ARG_1(x)	        DO_ARG_WORK(x)	
 
#define ARG_1(x, ...)	    Do_ARG_1(x)
#define ARG_2(x, ...)       ARG_1(x)	PREPARE_MACRO(ARG_1(__VA_ARGS__))
#define ARG_3(x, ...)	    ARG_1(x)	PREPARE_MACRO(ARG_2(__VA_ARGS__))
#define ARG_4(x, ...)	    ARG_1(x)	PREPARE_MACRO(ARG_3(__VA_ARGS__))
 
#define ADD_COMPONENT_PROPERTY_DESCRIPTION(...)     \
	PREPARE_MACRO(CAT(ARG_, ARG_COUNTX(__VA_ARGS__))(__VA_ARGS__))

class UIComponent: public Component {
    Q_OBJECT
public:
    COMPONENT_PROPERTY(std::vector<std::shared_ptr<ComponentPropertyDescription>>, PropertyDescriptions, propertyDescriptions, {})
    COMPONENT_PROPERTY(std::shared_ptr<ComponentDescription>, ComponentDescription, componentDescription, nullptr)

    UIComponent() = default;
    UIComponent(int componentId, int entityId):Component(componentId,entityId){}

    virtual ~UIComponent(){}

    virtual void MakeComponentPropertyDescriptions() {}

};

}
#endif //CFRENDERENGINE_UICOMPONENT_H

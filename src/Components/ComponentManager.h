//
// Created by fordchen on 2021/8/31.
//

#ifndef CFRENDERENGINE_COMPONENTMANAGER_H
#define CFRENDERENGINE_COMPONENTMANAGER_H

#include <QString>
#include <QObject>

#include <vector>

#include "component.h"
#include "Primitive/Triangle.h"

class ComponentManager {
public:

    static std::vector<ComponentDescription*> allComponentDescriptions_;

    static void registerComponentDescriptions() {
        ComponentDescription* triangle = new ComponentDescription;
        triangle->type_ = ComponentType::kTriangle;
        triangle->label_ = QObject::tr("Triangle");
        triangle->group_ = ComponentGroup::kPrimitive;

        allComponentDescriptions_.emplace_back(triangle);
    }

    static std::vector<Component*> getComponents(){
        std::vector<Component*> coms;

        coms.push_back(new Triangle(001,1));

        return coms;
    }
};



#endif //CFRENDERENGINE_COMPONENTMANAGER_H

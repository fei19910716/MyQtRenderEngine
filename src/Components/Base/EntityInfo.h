#pragma once
#include "Components/Base/Component.h"

#include <vector>

namespace render{
class EntityInfo: public Component
{
    Q_OBJECT
public:

    COMPONENT_PROPERTY(QString, EntityId, entityId, "")
    COMPONENT_PROPERTY(QString, Label, label, "")

public:
    EntityInfo(QString entityId, QString label):
        entityId_(entityId),
        label_(label)
    {

    }
    ~EntityInfo(){}
};

}
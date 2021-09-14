#pragma once
#include "Components/Base/Component.h"

#include <vector>

CFENGINE_RENDER_START
class EntityInfo: public Component
{
    Q_OBJECT
public:
    /**
     * 记录entity的id
     */
    QString entityId_;
    QString label_;

public:
    EntityInfo(){}
    EntityInfo(QString entityId, QString label):
        entityId_(entityId),
        label_(label)
    {

    }
    ~EntityInfo(){}
};

CFENGINE_RENDER_END
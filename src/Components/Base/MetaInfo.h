#pragma once
#include "Components/Base/component.h"

#include <vector>

#include "Core/entityx.h"

class MetaInfo: public Component
{
    Q_OBJECT
public:
    /**
     * 记录entity的id
     */
    QString entityId_;
    QString label_;

public:
    MetaInfo(){}
    MetaInfo(QString entityId,QString label):
        entityId_(entityId),
        label_(label)
    {

    }
    ~MetaInfo(){}
};


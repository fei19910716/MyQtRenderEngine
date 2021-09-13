#pragma once
#include "Components/Base/cfcomponent.h"

#include <vector>


class MetaInfo: public CFComponent
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


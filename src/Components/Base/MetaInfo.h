#pragma once
#include "Components/Base/component.h"

#include <vector>

#include "Core/entityx.h"

class MetaInfo: public Component
{
    Q_OBJECT
public:
    
    QString entityId_;
    QString label_;

    CFEntity* entity_;

    std::vector<MetaInfo> children_;
    MetaInfo* parent_;
public:
    MetaInfo(){}
    MetaInfo(QString entityId,QString label,std::vector<MetaInfo>&& children): 
        entityId_(entityId),
        label_(label),
        children_(children),
        entity_(nullptr)
    {

    }
    ~MetaInfo(){}
};


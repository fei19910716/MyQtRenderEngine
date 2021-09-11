#pragma once
#include "Components/Base/component.h"

#include <vector>

class MetaInfo: public Component
{
public:
    
    QString entityId_;
    QString label_;

    std::vector<MetaInfo> children_;
public:
    MetaInfo(QString entityId,QString label,std::vector<MetaInfo>&& children): 
    entityId_(entityId),
    label_(label),
    children_(children)
    {

    }
    ~MetaInfo(){}
};


//
// Created by fordchen on 2021/9/13.
//

#ifndef CFRENDERENGINE_CFENTITY_H
#define CFRENDERENGINE_CFENTITY_H

#include <QObject>

#include <tuple>

#include "Core/entityx.h"
#include "Components/Base/Component.h"
class CFEntity: public QObject {
    Q_OBJECT
public:
    CFEntity();
    CFEntity(const CFEntity &other);
    explicit CFEntity(QString entityId, QString name);
    ~CFEntity();

    bool valid();

    void addChild(CFEntity* child);
    void removeChild(CFEntity* child);

    template<typename T>
    T* component(){
        auto com = ENTT::registry.try_get<T>(entity_);
        return com;
    }


    template<typename T, typename... ARG>
    bool addComponent(ARG&&... args){
        auto com = ENTT::registry.try_get<T>(entity_);
        if(com == nullptr){
            ENTT::registry.emplace<T>(entity_, std::forward<ARG>(args)...);
            return true;
        }else{
            ENTT::registry.replace<T>(entity_, std::forward<ARG>(args)...);
            return true;
        }
    }

    template<typename T>
    void removeComponent(){
        ENTT::registry.remove<T>(entity_);
    }
public:
    ENTTEntity entity_;

    CFEntity* parent_ = nullptr;
    std::vector<CFEntity*> children_;
};


#endif //CFRENDERENGINE_CFENTITY_H

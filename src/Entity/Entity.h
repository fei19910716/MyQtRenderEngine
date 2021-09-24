//
// Created by fordchen on 2021/9/13.
//

#ifndef CFRENDERENGINE_ENTITY_H
#define CFRENDERENGINE_ENTITY_H

#include <QObject>

#include <tuple>

#include "Core/entityx.h"
#include "Components/Base/Component.h"

namespace render{
class Entity: public QObject {
    Q_OBJECT
public:
    Entity();
    Entity(const Entity &other);
    explicit Entity(QString entityId, QString name);
    ~Entity();

    bool valid();

    void addChild(Entity* child);
    void removeChild(Entity* child);

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

    Entity* parent_ = nullptr;
    std::vector<Entity*> children_;
};

}
#endif //CFRENDERENGINE_ENTITY_H

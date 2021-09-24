#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include <vector>

#include "Entity.h"
#include "Components/Base/Component.h"

namespace render{
class EntityManager : public QObject{
    Q_OBJECT
public:

    static Entity* createEntity(QString entityId, QString name, Entity* parent = nullptr);

    static void deleteEntity(Entity* entity);

    static Entity* root();

    static bool addComponentWithType(Entity* entity, render::ComponentType type);

    static std::vector<render::Component*> allComponents(Entity* entity);

private:
    template<typename... Args>
    static void allComponentsGetter(std::vector<render::Component*>& components, std::tuple<Args...> tup){
        //    cout << get<0>(tup) << ((tuple_size<decltype(tup)>::value > 1) ? ", " : "");
        //    cout << tup._Myfirst._Val << ((tuple_size<decltype(tup)>::value > 1) ? ", " : "");
        auto com = tup._Myfirst._Val;
        components.push_back(com);
        allComponentsGetter(components, tup._Get_rest());  //对除头1项之外的tup递归调用
    }
    template<>
    static void allComponentsGetter(std::vector<render::Component*>& components, std::tuple<> tup){

    }

public:
    static Entity* root_;
};
}
#endif // ENTITY_H

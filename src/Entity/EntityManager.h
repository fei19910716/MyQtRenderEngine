#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

#include <vector>

#include "CFEntity.h"
#include "Components/Base/Component.h"
class EntityManager : public QObject{
    Q_OBJECT
public:

    static CFEntity* createEntity(QString entityId, QString name, CFEntity* parent = nullptr);

    static void deleteEntity(CFEntity* entity);

    static CFEntity* root();

    static bool addComponentWithType(CFEntity* entity, CFEngineRender::ComponentType type);

    static std::vector<CFEngineRender::Component*> allComponents(CFEntity* entity);

private:
    template<typename... Args>
    static void allComponentsGetter(std::vector<CFEngineRender::Component*>& components, std::tuple<Args...> tup){
        //    cout << get<0>(tup) << ((tuple_size<decltype(tup)>::value > 1) ? ", " : "");
        //    cout << tup._Myfirst._Val << ((tuple_size<decltype(tup)>::value > 1) ? ", " : "");
        auto com = tup._Myfirst._Val;
        components.push_back(com);
        allComponentsGetter(components, tup._Get_rest());  //对除头1项之外的tup递归调用
    }
    template<>
    static void allComponentsGetter(std::vector<CFEngineRender::Component*>& components, std::tuple<> tup){

    }

public:
    static CFEntity* root_;
};

#endif // ENTITY_H

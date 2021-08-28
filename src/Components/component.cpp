
#include "component.h"

Component::Component(QString&& _id, int entid):m_id(std::move(_id)),m_entityID(entid){}
Component::Component(const Component& com){
    this->m_id = com.id();
    this->m_entityID = com.entityID();
}

std::vector<Component> Component::getComponents(){
    std::vector<Component> coms;
    coms.push_back(Component("one",1));
    coms.push_back(Component("two",2));
    coms.push_back(Component("one",1));
    coms.push_back(Component("two",2));

    coms.push_back(Component("one",1));
    coms.push_back(Component("two",2));
    coms.push_back(Component("one",1));
    coms.push_back(Component("two",2));
    return coms;
}
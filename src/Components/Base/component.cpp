
#include "component.h"


Component::Component(int componentId, int entityId):componentId_(componentId),entityId_(entityId){

}
Component::Component(const Component& com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
}

Component &Component::operator =(const Component &com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
    return *this;
}




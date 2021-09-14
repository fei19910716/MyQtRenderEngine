
#include "Component.h"


CFEngineRender::Component::Component(int componentId, int entityId):componentId_(componentId),entityId_(entityId){

}

CFEngineRender::Component::~Component() noexcept {

}
CFEngineRender::Component::Component(const Component& com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
}

CFEngineRender::Component &CFEngineRender::Component::operator =(const Component &com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
    return *this;
}





#include "cfcomponent.h"


CFComponent::CFComponent(int componentId, int entityId):componentId_(componentId),entityId_(entityId){

}

CFComponent::~CFComponent() noexcept {
    for(auto& item: propertyDescriptions_){
        delete item;
    }

    delete componentDescription_;
}
CFComponent::CFComponent(const CFComponent& com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
}

CFComponent &CFComponent::operator =(const CFComponent &com){
    this->componentId_ = com.componentId();
    this->entityId_ = com.entityId();
    return *this;
}




#include "System.h"

namespace render{

System::System():GL(){

}

void System::configure(entt::registry &registry) {

}

std::shared_ptr<Renderer> System::update(entt::registry &registry, float dt) {
    return nullptr;
}
}
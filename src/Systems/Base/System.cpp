#include "System.h"

CFENGINE_RENDER_START

System::System():GL(){

}

void System::configure(entt::registry &registry) {

}

std::shared_ptr<Renderer> System::update(entt::registry &registry, float dt) {
    return nullptr;
}
CFENGINE_RENDER_END
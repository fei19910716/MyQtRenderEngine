#include "System.h"


CFEngineRender::System::System():GL(){

}

void CFEngineRender::System::configure(entt::registry &registry) {

}

std::shared_ptr<CFEngineRender::Renderer> CFEngineRender::System::update(entt::registry &registry, float dt) {
    return nullptr;
}

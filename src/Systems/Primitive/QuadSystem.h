#pragma once

#include "Systems/Base/System.h"
#include "Components/Primitive/Quad.h"

CFENGINE_RENDER_START
class QuadSystem: public System{
public:
    QuadSystem();

    std::shared_ptr<Renderer> update(entt::registry &registry, float dt) override;

private:
    QString vertexShader_ = ":/shader/simple/simple.vert";

    QString fragmentShader_ = ":/shader/simple/simple.frag";
};
CFENGINE_RENDER_END

#pragma once

#include "Systems/Base/System.h"
#include "Components/Primitive/Quad.h"

namespace render{
class QuadSystem: public System{
public:
    QuadSystem();

    std::shared_ptr<Renderer> update(entt::registry &registry, float dt) override;

private:
    QString vertexShader_ = ":/shader/primitive/primitive.vert";

    QString fragmentShader_ = ":/shader/primitive/primitive.frag";
};
}

#pragma once

#include <QString>

#include "Systems/Base/System.h"

namespace render{
    class CubeSystem: public System{
    public:

        std::shared_ptr<Renderer> update(entt::registry &registry, float dt) override;

    private:
        QString vertexShader_ = ":/shader/primitive/primitive.vert";

        QString fragmentShader_ = ":/shader/primitive/primitive.frag";
    };
}

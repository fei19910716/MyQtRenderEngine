
#pragma once

#include "Core/entityx.h"
#include "Core/GL.h"
#include "Render/Renderer/Renderer.h"

CFENGINE_RENDER_START

class System:public GL{
public:

    System();

    virtual void configure(entt::registry &registry);
    virtual std::shared_ptr<Renderer> update(entt::registry &registry, float dt);

};

CFENGINE_RENDER_END
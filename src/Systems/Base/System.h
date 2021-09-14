
#pragma once

#include "Core/entityx.h"
#include <QOpenGLFunctions_3_3_Core>

#include "Render/Renderer/Renderer.h"

CFENGINE_RENDER_START

class System: public QOpenGLFunctions_3_3_Core{
public:

    virtual void configure(entt::registry &registry){}
    virtual std::shared_ptr<Renderer> update(entt::registry &registry, float dt){return nullptr;}

};

CFENGINE_RENDER_END
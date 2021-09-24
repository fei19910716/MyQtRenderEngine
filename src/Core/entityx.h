#pragma once

#include <entt/entt.hpp>

namespace render{

using ENTTEntity = entt::registry::entity_type;

class ENTT{
public:
    static entt::registry registry;
};

}
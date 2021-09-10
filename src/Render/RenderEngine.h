#pragma once
#include <QObject>
#include <QOpenGLFunctions_3_3_Core>

#include <vector>

#include "Systems/Primitive/TriangleSystem.h"
#include "Components/ComponentManager.h"

class RenderEngine : public QObject ,public QOpenGLFunctions_3_3_Core{
  Q_OBJECT
public:
  entt::registry m_registry;
  std::vector<System*> m_systems;

  int m_width,m_height;
  unsigned int m_vao,m_vbo,m_fbo,m_texture,m_rbo,m_ebo;

  explicit RenderEngine(){
      ComponentManager::registerComponentDescriptions();

      entt::registry::entity_type entity = m_registry.create();
      m_registry.emplace<Triangle>(entity);

      m_systems.push_back(new TriangleSystem());
  }

  void update(float dt){
    for (System *system : m_systems) {
        system->update(m_registry, dt);
    }
  }

  void setRenderSize(int width,int height);
};
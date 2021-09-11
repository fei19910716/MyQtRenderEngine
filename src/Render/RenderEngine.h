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

  explicit RenderEngine();

  void update(float dt);

  void setRenderSize(int width,int height);
};
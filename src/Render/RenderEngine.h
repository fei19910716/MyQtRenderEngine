#pragma once
#include <QObject>
#include <QSize>
#include <QOpenGLFunctions_3_3_Core>

#include <vector>

#include "Systems/Primitive/TriangleSystem.h"
#include "Components/ComponentManager.h"

class RenderEngine : public QObject ,public QOpenGLFunctions_3_3_Core{
  Q_OBJECT
public:
  explicit RenderEngine();
  /**
   * 释放GL资源
   */
  ~RenderEngine();

  void update(float dt);

  void setRenderSize(int width,int height);
  void genNewTexture(GLuint* texture, QSize size);

public:
    std::vector<System*> m_systems;

    int m_width,m_height;
    unsigned int m_fbo,m_rbo;

    unsigned int m_textureToDisplay, m_textureToRender, m_textureToDelete;
};
#pragma once
#include <QObject>
#include <QSize>
#include <QOpenGLFunctions_3_3_Core>

#include <vector>

#include "Core/Core.h"
#include "Systems/Primitive/TriangleSystem.h"
#include "Components/ComponentManager.h"
#include "Render/Base/RenderBuffer.h"
#include "Render/Base/FrameBuffer.h"
#include "Render/Base/Texture.h"

#include "Render/Renderer/Renderer.h"

CFENGINE_RENDER_START

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

public:
    std::vector<System*> m_systems;

    int m_width,m_height;

    std::shared_ptr<Renderer> renderer_;

    std::shared_ptr<RenderBuffer> rbo_;
    std::shared_ptr<FrameBuffer> fbo_;
    std::shared_ptr<Texture> textureToDisplay_,textureToRender_,textureToDelete_;
};

CFENGINE_RENDER_END
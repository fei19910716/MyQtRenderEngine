#pragma once
#include <QObject>
#include <QSize>

#include <vector>

#include "Core/Core.h"
#include "Components/ComponentManager.h"

CFENGINE_RENDER_START
class RenderQueue;
class System;
class FrameBuffer;
class Texture;
class RenderBuffer;
class RenderEngine : public QObject {
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
    std::shared_ptr<RenderQueue> renderQueue;
    std::shared_ptr<RenderBuffer> rbo_;
    std::shared_ptr<FrameBuffer> fbo_;
    std::shared_ptr<Texture> textureToDisplay_,textureToRender_,textureToDelete_;
};

CFENGINE_RENDER_END
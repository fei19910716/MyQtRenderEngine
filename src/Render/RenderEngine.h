#pragma once
#include <QObject>
#include <QSize>

#include <vector>

#include "Components/ComponentManager.h"

namespace render{
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

    /**
     * 子线程初始的渲染尺寸
     */
    int width_ = 960;
    int height_ = 1280;

    std::shared_ptr<RenderQueue> renderQueue;
    std::shared_ptr<RenderBuffer> rbo_;
    std::shared_ptr<FrameBuffer> fbo_;
    std::shared_ptr<Texture> textureToDisplay_,textureToRender_,textureToDelete_;
};

}
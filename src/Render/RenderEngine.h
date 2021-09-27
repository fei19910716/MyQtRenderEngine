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

  void update(float dt);

  void setRenderSize(int width,int height);

public:
    std::vector<std::shared_ptr<System>> m_systems;

    /**
     * 子线程初始的渲染尺寸
     */
    int render_width_ = 960;
    int render_height_ = 1280;

    std::shared_ptr<RenderQueue> renderQueue;
    std::shared_ptr<Texture> textureToDisplay_,textureToRender_,textureToDelete_;
};

}
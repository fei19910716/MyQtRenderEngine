//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_FRAMEBUFFER_H
#define CFRENDERENGINE_FRAMEBUFFER_H

#include <memory>

#include "GLResource.h"

CFENGINE_RENDER_START

class Texture;
class RenderBuffer;

class FrameBuffer : public GLResource{
public:
    FrameBuffer(bool validFBO = true);
    FrameBuffer(unsigned int width, unsigned int height);

    ~FrameBuffer();

    void use();
    void bindTexture(std::shared_ptr<Texture> texture);
    void bindRenderBuffer(std::shared_ptr<RenderBuffer> renderBuffer);

    std::shared_ptr<Texture> texture();
    std::shared_ptr<RenderBuffer> renderBuffer();
private:
    std::shared_ptr<Texture> texture_;
    std::shared_ptr<RenderBuffer> rbo_;
};

CFENGINE_RENDER_END

#endif //CFRENDERENGINE_FRAMEBUFFER_H

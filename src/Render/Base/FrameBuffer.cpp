//
// Created by fordchen on 2021/9/14.
//

#include "FrameBuffer.h"

#include "Render/Base/Texture.h"
#include "Render/Base/RenderBuffer.h"
CFENGINE_RENDER_START

FrameBuffer::FrameBuffer(bool validFBO): GLResource() {
    if(validFBO)
        glGenFramebuffers(1, &handle_);
    else
        handle_ = 0;

    std::cout << "----------FrameBuffer()--" << handle_ << std::endl;
}

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height) {
    glGenFramebuffers(1, &handle_);

    auto texture = std::make_shared<Texture>(width,height);
    auto rbo_ = std::make_shared<RenderBuffer>(width,height);

    this->bindRenderBuffer(rbo_);
    this->bindTexture(texture);

    std::cout << "----------FrameBuffer()--" << handle_ << std::endl;
}


std::shared_ptr<Texture> FrameBuffer::texture() {
    return texture_;
}

std::shared_ptr<RenderBuffer> FrameBuffer::renderBuffer() {
    return rbo_;
}

void FrameBuffer::use() {
    glBindFramebuffer(GL_FRAMEBUFFER, handle_);
}

void FrameBuffer::bindTexture(std::shared_ptr<Texture> texture) {
    texture_ = texture;
    glBindFramebuffer(GL_FRAMEBUFFER, handle_);
    glBindTexture(GL_TEXTURE_2D,texture->handle());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->handle(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindRenderBuffer(std::shared_ptr<RenderBuffer> renderBuffer) {
    rbo_ = renderBuffer;

    glBindFramebuffer(GL_FRAMEBUFFER, handle_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->handle());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
    std::cout << "~FrameBuffer()--" << handle_<< std::endl;
    glDeleteFramebuffers(1, &handle_);
}

CFENGINE_RENDER_END




//
// Created by fordchen on 2021/9/14.
//

#include "RenderBuffer.h"

CFEngineRender::RenderBuffer::RenderBuffer(unsigned int width, unsigned int height):GLResource() {
    glGenRenderbuffers(1, &handle_);
    glBindRenderbuffer(GL_RENDERBUFFER, handle_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    std::cout << "----------RenderBuffer()--" << handle_ << std::endl;
}

CFEngineRender::RenderBuffer::~RenderBuffer() {
    std::cout << "~RenderBuffer()--" << handle_ << std::endl;
    glDeleteFramebuffers(1, &handle_);
}

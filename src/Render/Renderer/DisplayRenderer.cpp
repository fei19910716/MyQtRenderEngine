//
// Created by fordchen on 2021/9/14.
//

#include "DisplayRenderer.h"

CFEngineRender::DisplayRenderer::DisplayRenderer() : display_width_(0), display_height_(0) {

}

CFEngineRender::DisplayRenderer::~DisplayRenderer() noexcept {

}

void CFEngineRender::DisplayRenderer::bindOutput() {
    // 首先将输入的FBO直接作为输出,因为这个render只做显示用，不渲染其他
    setOutput(this->input_.front());
    // 绑定到默认FBO
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glViewport(0,0,display_width_,display_height_);
}

void CFEngineRender::DisplayRenderer::setDisplaySize(unsigned int width, unsigned int height) {
    this->display_width_ = width;
    this->display_height_ = height;
}


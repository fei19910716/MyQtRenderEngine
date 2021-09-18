//
// Created by fordchen on 2021/9/14.
//

#include "Renderer.h"

CFEngineRender::Renderer::Renderer() {

}

bool CFEngineRender::Renderer::enable() {
    return enable_;
}

void CFEngineRender::Renderer::setEnable(bool enable) {
    enable_ = enable;
}

std::string & CFEngineRender::Renderer::id() {
    return id_;
}

void CFEngineRender::Renderer::setId(std::string id) {
    id_ = id;
}

std::string & CFEngineRender::Renderer::parentId() {
    return parent_id_;
}

void CFEngineRender::Renderer::setParentId(std::string parentId) {
    parent_id_ = parentId;
}

std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> &CFEngineRender::Renderer::input() {
    return input_;
}

void CFEngineRender::Renderer::setInput(std::shared_ptr<CFEngineRender::FrameBuffer> frame_buffer) {
    input_.clear();
    input_.push_back(frame_buffer);
}

void CFEngineRender::Renderer::setInput(std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> frame_buffers) {
    input_.clear();
    input_.insert(this->input_.end(), frame_buffers.begin(), frame_buffers.end());
}

void CFEngineRender::Renderer::setOutput(std::shared_ptr<CFEngineRender::FrameBuffer> frame_buffer) {
    output_ = frame_buffer;
}

std::shared_ptr<CFEngineRender::FrameBuffer> CFEngineRender::Renderer::output() {
    return output_;
}

void CFEngineRender::Renderer::setRenderSize(unsigned int width, unsigned int height) {
    render_width_ = width;
    render_height_ = height;
}

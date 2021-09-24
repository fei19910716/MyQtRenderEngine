//
// Created by fordchen on 2021/9/14.
//

#include "Renderer.h"

namespace render{
Renderer::Renderer() {

}

bool Renderer::enable() {
    return enable_;
}

void Renderer::setEnable(bool enable) {
    enable_ = enable;
}

std::string & Renderer::id() {
    return id_;
}

void Renderer::setId(std::string id) {
    id_ = id;
}

std::string & Renderer::parentId() {
    return parent_id_;
}

void Renderer::setParentId(std::string parentId) {
    parent_id_ = parentId;
}

std::vector<std::shared_ptr<FrameBuffer>> &Renderer::input() {
    return input_;
}

void Renderer::setInput(std::shared_ptr<FrameBuffer> frame_buffer) {
    input_.clear();
    input_.push_back(frame_buffer);
}

void Renderer::setInput(std::vector<std::shared_ptr<FrameBuffer>> frame_buffers) {
    input_.clear();
    input_.insert(this->input_.end(), frame_buffers.begin(), frame_buffers.end());
}

void Renderer::setOutput(std::shared_ptr<FrameBuffer> frame_buffer) {
    output_ = frame_buffer;
}

std::shared_ptr<FrameBuffer> Renderer::output() {
    return output_;
}

void Renderer::setRenderSize(unsigned int width, unsigned int height) {
    render_width_ = width;
    render_height_ = height;
}
}
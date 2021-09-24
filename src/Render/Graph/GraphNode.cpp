//
// Created by fordchen on 2021/9/16.
//

#include "GraphNode.h"

#include <algorithm>

namespace render{
GraphNode::GraphNode(std::shared_ptr<Renderer> renderer): renderer_(renderer) , layer_(0){

}

void GraphNode::addNext(std::shared_ptr<GraphNode> next_node) {
    auto it = std::find(next_nodes_.begin(),next_nodes_.end(),next_node);
    if(it != next_nodes_.end()){
        return; // 已经添加
    }
    next_nodes_.push_back(next_node);
}

void GraphNode::addInput(std::shared_ptr<FrameBuffer> frame_buffer) {
    renderer_->setInput(frame_buffer);
}

void GraphNode::addInput(std::vector<std::shared_ptr<FrameBuffer>>& frame_buffers) {
    renderer_->setInput(frame_buffers);
}

std::vector<std::shared_ptr<GraphNode>> &GraphNode::nextNodes() {
    return next_nodes_;
}

std::shared_ptr<Renderer> GraphNode::renderer() {
    return renderer_;
}

unsigned int GraphNode::layer() {
    return layer_;
}

std::vector<std::shared_ptr<FrameBuffer>> &GraphNode::input() {
    return renderer_->input();
}

bool GraphNode::enable() {
    return renderer_->enable();
}

void GraphNode::setLayer(unsigned int layer) {
    layer_ = layer;
}
}
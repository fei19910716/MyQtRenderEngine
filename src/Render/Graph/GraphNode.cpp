//
// Created by fordchen on 2021/9/16.
//

#include "GraphNode.h"

#include <algorithm>

CFEngineRender::GraphNode::GraphNode(std::shared_ptr<Renderer> renderer): renderer_(renderer) , layer_(0){

}

void CFEngineRender::GraphNode::addNext(std::shared_ptr<GraphNode> next_node) {
    auto it = std::find(next_nodes_.begin(),next_nodes_.end(),next_node);
    if(it != next_nodes_.end()){
        return; // 已经添加
    }
    next_nodes_.push_back(next_node);
}

void CFEngineRender::GraphNode::addInput(std::shared_ptr<CFEngineRender::FrameBuffer> frame_buffer) {
    auto input = renderer_->input();
    auto it = std::find(input.begin(),input.end(),frame_buffer);
    if(it != input.end()){
        return; // 已经添加
    }
    input.push_back(frame_buffer);
}

void CFEngineRender::GraphNode::addInput(std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> frame_buffers) {
    auto input = renderer_->input();
    input.clear();
    input.insert(input.end(), frame_buffers.begin(),frame_buffers.end());
}

std::vector<std::shared_ptr<CFEngineRender::GraphNode>> &CFEngineRender::GraphNode::nextNodes() {
    return next_nodes_;
}

std::shared_ptr<CFEngineRender::Renderer> CFEngineRender::GraphNode::renderer() {
    return renderer_;
}

unsigned int CFEngineRender::GraphNode::layer() {
    return layer_;
}

std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> &CFEngineRender::GraphNode::input() {
    return renderer_->input();
}

bool CFEngineRender::GraphNode::enable() {
    return renderer_->enable();
}

void CFEngineRender::GraphNode::setLayer(unsigned int layer) {
    layer_ = layer;
}

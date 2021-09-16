//
// Created by fordchen on 2021/9/16.
//

#include "RenderQueue.h"

CFEngineRender::RenderQueue::RenderQueue() {

}

CFEngineRender::RenderQueue::~RenderQueue() {

}

void CFEngineRender::RenderQueue::addRenderer(std::shared_ptr<Renderer> renderer, std::string id) {
    if(tail_renderer_id_.empty()) {
        RenderGraph::addRenderer(renderer, id);
        tail_renderer_id_ = id;
    } else{
        this->addRenderer(renderer,id, tail_renderer_id_);
    }
}

void CFEngineRender::RenderQueue::addRenderer(std::shared_ptr<Renderer> renderer, std::string id, std::string parent_id) {
    RenderGraph::addRenderer(renderer, id, parent_id);
    this->connectRenderer(parent_id, id);
}

void CFEngineRender::RenderQueue::connectRenderer(std::string preId, std::string curId) {
    std::shared_ptr<GraphNode> preNode = renderer_map_[preId];
    std::shared_ptr<GraphNode> curNode = renderer_map_[curId];

    preNode->addNext(curNode);

    auto layer = preNode->layer() + 1 > curNode->layer() ? preNode->layer() + 1 : curNode->layer();
    curNode->setLayer(layer);

    auto iter = std::find(start_nodes_.begin(), start_nodes_.end(), curNode);
    if (iter != start_nodes_.end()) {
        start_nodes_.erase(iter);
    }
    node_list_ = nullptr;
}



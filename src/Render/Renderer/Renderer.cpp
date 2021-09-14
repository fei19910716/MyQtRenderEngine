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
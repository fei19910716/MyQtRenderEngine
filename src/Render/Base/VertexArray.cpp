//
// Created by fordchen on 2021/9/14.
//

#include "VertexArray.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

CFEngineRender::VertexArray::VertexArray(): GLResource() {
    glGenVertexArrays(1, &handle_);
    glBindVertexArray(handle_);
}

void CFEngineRender::VertexArray::use() {
    glBindVertexArray(handle_);
}

void CFEngineRender::VertexArray::bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
    vbo_ = vertexBuffer;
    glBindVertexArray(handle_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->handle());
    glBindVertexArray(0);
}

void CFEngineRender::VertexArray::bindIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
    ibo_ = indexBuffer;
    glBindVertexArray(handle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->handle());
    glBindVertexArray(0);
}

unsigned int CFEngineRender::VertexArray::vertexCount() {
    return ibo_->vertexCount();
}

CFEngineRender::VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &handle_);
    handle_ = 0;
}

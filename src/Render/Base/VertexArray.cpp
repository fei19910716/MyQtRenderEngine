//
// Created by fordchen on 2021/9/14.
//

#include "VertexArray.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace render{
VertexArray::VertexArray(): GLResource() {
    glGenVertexArrays(1, &handle_);
    glBindVertexArray(handle_);
}

void VertexArray::use() {
    glBindVertexArray(handle_);
}

void VertexArray::bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) {
    vbo_ = vertexBuffer;
    glBindVertexArray(handle_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->handle());
    glBindVertexArray(0);
}

void VertexArray::bindIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) {
    ibo_ = indexBuffer;
    glBindVertexArray(handle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->handle());
    glBindVertexArray(0);
}

unsigned int VertexArray::vertexCount() {
    return ibo_->vertexCount();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &handle_);
}
}
//
// Created by fordchen on 2021/9/14.
//

#include "VertexBuffer.h"

CFEngineRender::VertexBuffer::VertexBuffer(std::vector<float>& vertices): GLResource(){
    vertex_count_ = vertices.size();
    glGenBuffers(1, &handle_);
    glBindBuffer(GL_ARRAY_BUFFER, handle_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_count_, vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void CFEngineRender::VertexBuffer::release() {
    glDeleteBuffers(1, &handle_);
}

unsigned int CFEngineRender::VertexBuffer::vertexCount() {
    return vertex_count_;
}


//
// Created by fordchen on 2021/9/14.
//

#include "IndexBuffer.h"


CFEngineRender::IndexBuffer::IndexBuffer(std::vector<unsigned int>& indices) : GLResource(){
    glGenBuffers(1, &handle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void CFEngineRender::IndexBuffer::release() {
    glDeleteBuffers(1, &handle_);
}

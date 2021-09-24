//
// Created by fordchen on 2021/9/14.
//

#include "IndexBuffer.h"

namespace render{

IndexBuffer::IndexBuffer(std::vector<unsigned int>& indices) : GLResource(){
    vertex_count_ = indices.size();
    glGenBuffers(1, &handle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

unsigned int IndexBuffer::vertexCount() {
    return vertex_count_;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &handle_);
}

}

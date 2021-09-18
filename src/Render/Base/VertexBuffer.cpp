//
// Created by fordchen on 2021/9/14.
//

#include "VertexBuffer.h"
#include <QDebug>
CFEngineRender::VertexBuffer::VertexBuffer(std::vector<float>& vertices, std::shared_ptr<VertexLayout> layout): GLResource(){
    glGenBuffers(1, &handle_);
    glBindBuffer(GL_ARRAY_BUFFER, handle_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    auto stride = layout->m_stride;
    for(auto ite = layout->m_attribute.begin(); ite != layout->m_attribute.end(); ite++){
        auto key = (*ite).first;
        auto info = (*ite).second;
        glVertexAttribPointer(key, info.num, info.type, GL_FALSE, stride * info.typeSize, (void*)(info.offset * info.typeSize));
        glEnableVertexAttribArray(key);
    }
}

void CFEngineRender::VertexBuffer::release() {
    glDeleteBuffers(1, &handle_);
}


//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_VERTEXARRAY_H
#define CFRENDERENGINE_VERTEXARRAY_H

#include <memory>

#include "GLResource.h"

CFENGINE_RENDER_START

class VertexBuffer;
class IndexBuffer;

class VertexArray : public GLResource{
public:
    VertexArray();

    void use();
    void bindVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
    void bindIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

    void release() override;

    unsigned int vertexCount();

private:
    std::shared_ptr<VertexBuffer> vbo_;
    std::shared_ptr<IndexBuffer> ibo_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_VERTEXARRAY_H

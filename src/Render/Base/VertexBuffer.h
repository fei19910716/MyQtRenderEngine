//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_VERTEXBUFFER_H
#define CFRENDERENGINE_VERTEXBUFFER_H

#include <cstdint>
#include "GLResource.h"

CFENGINE_RENDER_START
class VertexBuffer: public GLResource {
public:
    VertexBuffer(std::vector<float>& vertices);

    void release() override;

    unsigned int vertexCount();

private:
    unsigned int vertex_count_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_VERTEXBUFFER_H

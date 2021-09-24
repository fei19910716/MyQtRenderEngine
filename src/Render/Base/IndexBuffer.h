//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_INDEXBUFFER_H
#define CFRENDERENGINE_INDEXBUFFER_H

#include <cstdint>

#include "GLResource.h"

namespace render{

class IndexBuffer: public GLResource {
public:
    IndexBuffer(std::vector<unsigned int>& indices);

    ~IndexBuffer();
    unsigned int vertexCount();

private:
    unsigned int vertex_count_;

};

}
#endif //CFRENDERENGINE_INDEXBUFFER_H

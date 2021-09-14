//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_INDEXBUFFER_H
#define CFRENDERENGINE_INDEXBUFFER_H

#include <cstdint>

#include "GLResource.h"

CFENGINE_RENDER_START

class IndexBuffer: public GLResource {
public:
    IndexBuffer(std::vector<unsigned int>& indices);

    void release() override;
private:

};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_INDEXBUFFER_H

//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_RENDERBUFFER_H
#define CFRENDERENGINE_RENDERBUFFER_H

#include "GLResource.h"

CFENGINE_RENDER_START

class RenderBuffer : public GLResource{

public:
    RenderBuffer(unsigned int width, unsigned int height);

    ~RenderBuffer();

private:

};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_RENDERBUFFER_H

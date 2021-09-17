#ifndef CFRENDERENGINE_GLRESOURCE_H
#define CFRENDERENGINE_GLRESOURCE_H

#include "Core/GL.h"

CFENGINE_RENDER_START
class GLResource : public GL{
public:
    GLResource();
    unsigned int handle() const;

    virtual void release() = 0;
    virtual bool valid();
protected:
    unsigned int handle_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_GLRESOURCE_H

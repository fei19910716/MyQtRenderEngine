#ifndef CFRENDERENGINE_GLRESOURCE_H
#define CFRENDERENGINE_GLRESOURCE_H

#include "Core/GL.h"
#include <iostream>

namespace render{
class GLResource : public GL{
public:
    GLResource();
    unsigned int handle() const;

    virtual bool valid();
protected:
    unsigned int handle_;
};

}
#endif //CFRENDERENGINE_GLRESOURCE_H

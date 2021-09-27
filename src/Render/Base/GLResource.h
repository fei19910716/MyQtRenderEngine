#pragma once

#include "Core/GL.h"
#include <iostream>

#define INVALID_HANDLE 0

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


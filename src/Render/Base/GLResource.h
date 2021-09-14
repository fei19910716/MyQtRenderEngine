//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_GLRESOURCE_H
#define CFRENDERENGINE_GLRESOURCE_H

#include "Core/Core.h"

#include <QOpenGLFunctions_3_3_Core>

CFENGINE_RENDER_START
class GLResource : public QOpenGLFunctions_3_3_Core{
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

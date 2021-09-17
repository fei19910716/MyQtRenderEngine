#pragma once

#include "Core.h"
#include <QOpenGLFunctions_3_3_Core>
CFENGINE_RENDER_START
class GL: public QOpenGLFunctions_3_3_Core{
public:
    GL(){
        initializeOpenGLFunctions();
    }
};
CFENGINE_RENDER_END
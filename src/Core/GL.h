#pragma once

#include "Core.h"
#include <QOpenGLFunctions_3_3_Core>
CFENGINE_RENDER_START
class GL: public QOpenGLFunctions_3_3_Core{
public:
    GL();
};

#define ASSET(x) if(!(x)) __debugbreak(); // __debugBreak()是msvc编译器的中断函数
#define GLCALL(x) GLClearError(QOpenGLContext::currentContext());\
x;\
ASSET(GLLogCall(#x, __FILE__, __LINE__, QOpenGLContext::currentContext())) // 输出函数名、文件名、行号

void GLClearError(QOpenGLContext *context);

bool GLLogCall(const char* function, const char* file, int line, QOpenGLContext *context);

CFENGINE_RENDER_END
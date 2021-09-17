
#include "GL.h"
#include <iostream>
CFEngineRender::GL::GL(){
    initializeOpenGLFunctions();
}

void CFEngineRender::GLClearError(QOpenGLContext *context){
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();
    while(f->glGetError() != GL_NO_ERROR);
}

bool CFEngineRender::GLLogCall(const char* function, const char* file, int line, QOpenGLContext *context){
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();
    while(GLenum error = f->glGetError()){
        std::cout << "[opengl error] (" << error << "): " <<
                  function << " " << file << ": "<< line << std::endl;
        return false;
    }
    return true;
}


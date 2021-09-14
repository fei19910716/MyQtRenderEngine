//
// Created by fordchen on 2021/9/14.
//

#include "GLResource.h"

unsigned int CFEngineRender::GLResource::handle() const {
    return handle_;
}

CFEngineRender::GLResource::GLResource() {
    initializeOpenGLFunctions();
}

bool CFEngineRender::GLResource::valid() {
    return handle_ != 0;
}

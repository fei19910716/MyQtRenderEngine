#include "GLResource.h"

unsigned int CFEngineRender::GLResource::handle() const {
    return handle_;
}

CFEngineRender::GLResource::GLResource(): GL() {

}

bool CFEngineRender::GLResource::valid() {
    return handle_ != 0;
}

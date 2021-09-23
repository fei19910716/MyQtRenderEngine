#include "GLResource.h"

CFENGINE_RENDER_START
unsigned int GLResource::handle() const {
    return handle_;
}

GLResource::GLResource(): GL() {

}

bool GLResource::valid() {
    return handle_ != 0;
}

CFENGINE_RENDER_END

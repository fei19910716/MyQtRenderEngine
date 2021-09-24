#include "GLResource.h"

namespace render{
unsigned int GLResource::handle() const {
    return handle_;
}

GLResource::GLResource(): GL() {

}

bool GLResource::valid() {
    return handle_ != 0;
}

}

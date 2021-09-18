//
// Created by fordchen on 2021/9/14.
//

#include "Texture.h"

#include "Utils/RenderUtils.h"
#include <QOpenGLContext>

CFEngineRender::Texture::Texture(unsigned int width, unsigned int height): GLResource() {

    texture_width_ = width;
    texture_height_ = height;

    glGenTextures(1, &handle_);
    glBindTexture(GL_TEXTURE_2D, handle_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CFEngineRender::Texture::use(int unit) {
    GLCALL(glActiveTexture(GL_TEXTURE0 + unit))
    GLCALL(glBindTexture(GL_TEXTURE_2D, handle_))
}

void CFEngineRender::Texture::release() {
    glDeleteTextures(1, &handle_);
    handle_ = 0;
}

void CFEngineRender::Texture::setHandle(unsigned int value) {
    handle_ = value;
}

CFEngineRender::Texture::Texture(QString path) {
    handle_ = Utils::genTextureFromStbImage(path,&texture_width_,&texture_height_,QOpenGLContext::currentContext());
}

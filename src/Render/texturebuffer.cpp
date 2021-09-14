//
// Created by FordChen on 2021/1/11.
//

#include "TextureBuffer.h"
#include <QDebug>

#include "stb_image_write.h"

CFEngineRender::TextureBuffer *CFEngineRender::TextureBuffer::instance()
{
    static TextureBuffer m_instance;
    return &m_instance;
}

void CFEngineRender::TextureBuffer::createTexture(QOpenGLContext *context)
{
    context->functions()->glGenTextures(1, &m_texture);
}

void CFEngineRender::TextureBuffer::deleteTexture(QOpenGLContext *context) {

    context->functions()->glDeleteTextures(1,&m_texture);
}

void CFEngineRender::TextureBuffer::updateTexture(QOpenGLContext *context, int width, int height) {

    QMutexLocker locker(&m_mutex);
    //! 拷贝当前fbo中的纹理到m_texture中
    auto f= context->functions();
    f->glActiveTexture(GL_TEXTURE0);
    f->glBindTexture(GL_TEXTURE_2D,m_texture);
    f->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE, nullptr);
    f->glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,width,height,0);
    f->glBindTexture(GL_TEXTURE_2D,0);
    f->glFinish();
}

void CFEngineRender::TextureBuffer::updateTexture(QOpenGLContext *context, int textureID) {

    QMutexLocker locker(&m_mutex);
    m_texture=textureID;
}

void CFEngineRender::TextureBuffer::drawTexture(QOpenGLContext *context, int vertexCount) {

    QMutexLocker locker(&m_mutex);

    auto f = context->functions();

    f->glBindTexture(GL_TEXTURE_2D, m_texture);

    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    f->glActiveTexture(GL_TEXTURE0);
    f->glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    f->glBindTexture(GL_TEXTURE_2D, 0);
}

CFEngineRender::TextureBuffer::TextureBuffer():m_texture(0) {

}

CFEngineRender::TextureBuffer::~TextureBuffer() {

}

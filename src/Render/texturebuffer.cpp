//
// Created by FordChen on 2021/1/11.
//

#include "TextureBuffer.h"
#include <QDebug>
#include <QOpenGLFunctions_3_3_Core>

#include "Utils/RenderUtils.h"

CFENGINE_RENDER_START

TextureBuffer *TextureBuffer::instance()
{
    static TextureBuffer m_instance;
    return &m_instance;
}

void TextureBuffer::createTexture(QOpenGLContext *context)
{
    context->functions()->glGenTextures(1, &m_texture);
}

void TextureBuffer::deleteTexture(QOpenGLContext *context) {

    context->functions()->glDeleteTextures(1,&m_texture);
}

void TextureBuffer::updateTexture(QOpenGLContext *context, int width, int height) {

    QMutexLocker locker(&m_mutex);
    //! 拷贝当前fbo中的纹理到m_texture中
    auto f= context->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f->glActiveTexture(GL_TEXTURE0);
    f->glBindTexture(GL_TEXTURE_2D,m_texture);
    f->glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE, nullptr);
    f->glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,width,height,0);
    f->glBindTexture(GL_TEXTURE_2D,0);
    f->glFinish();

    {
        //! 调试用，保存渲染结果
        // Utils::saveCurrentFBOToImage(QSize(400,600),"D:\\GameEngine\\CFRenderEngine\\out12.png",context);

        // Utils::saveTextureToImage(m_texture,QSize(400,600),"D:\\GameEngine\\CFRenderEngine\\out11.png", context);
    }
}

void TextureBuffer::updateTexture(QOpenGLContext *context, int textureID) {

    QMutexLocker locker(&m_mutex);
    m_texture=textureID;
}

void TextureBuffer::drawTexture(QOpenGLContext *context, int vertexCount) {

    QMutexLocker locker(&m_mutex);

    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    f->glBindTexture(GL_TEXTURE_2D, m_texture);

    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    f->glActiveTexture(GL_TEXTURE0);
    f->glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    f->glBindTexture(GL_TEXTURE_2D, 0);

    {
        //! 调试用，保存渲染结果
        // Utils::saveCurrentFBOToImage(context,QSize(400,600),"D:\\GameEngine\\CFRenderEngine\\out21.png");

        // Utils::saveTextureToImage(context,m_texture,QSize(400,600),"D:\\GameEngine\\CFRenderEngine\\out22.png");
    }
}

TextureBuffer::TextureBuffer():m_texture(0) {

}

TextureBuffer::~TextureBuffer() {

}
CFENGINE_RENDER_END
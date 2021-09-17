//
// Created by fordchen on 2021/9/15.
//

#include "RenderUtils.h"

#include <QFile>
#include <QTextStream>

void Utils::saveTextureToImage(unsigned int texture, QSize size, std::string path,QOpenGLContext *context) {
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    unsigned char *data2 = new unsigned char[size.width() * size.height() * 4];
    f->glBindTexture(GL_TEXTURE_2D, texture);
    f->glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    stbi_write_png(path.c_str(), size.width(), size.height(), 4, data2, 0);
}

void Utils::saveCurrentFBOToImage( QSize size, std::string path,QOpenGLContext *context) {
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    unsigned char *data = new unsigned char[size.width() * size.height() * 4];
    // transfer the bind fbo image data, here is the opengl result data
    f->glReadPixels(0, 0, size.width(), size.height(), GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_write_png(path.c_str(), size.width(), size.height(), 4, data, 0);
}

void Utils::saveFBOToImage(unsigned int fbo, QSize size, std::string path,QOpenGLContext *context) {
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    f->glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    unsigned char *data = new unsigned char[size.width() * size.height() * 4];
    // transfer the bind fbo image data, here is the opengl result data
    f->glReadPixels(0, 0, size.width(), size.height(), GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_write_png(path.c_str(), size.width(), size.height(), 4, data, 0);
    f->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Utils::genTextureFromQImage(const QString &path, int* width, int* height,QOpenGLContext *context) {
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    unsigned int m_textureID;
    f->glGenTextures(1, &m_textureID);
    f->glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    QImage texImage, tempImage;
    bool isLoadOK = tempImage.load(path);
    if (isLoadOK) {
        // texImage = QGLWidget::convertToGLFormat(tempImage);
        *width = tempImage.width();
        *height = tempImage.height();
        f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage.width(), tempImage.height(), 0, GL_RGBA,
                        GL_UNSIGNED_BYTE, tempImage.bits());
        f->glGenerateMipmap(GL_TEXTURE_2D);
        f->glBindTexture(GL_TEXTURE_2D, 0);
    }

    return m_textureID;
}

unsigned int Utils::genTextureFromStbImage(const QString &path, int* width, int* height, QOpenGLContext *context) {
    auto f = context->versionFunctions<QOpenGLFunctions_3_3_Core>();

    unsigned int m_textureID;
    f->glGenTextures(1, &m_textureID);
    f->glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载并生成纹理
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.toStdString().c_str(), width, height, &nrChannels, 0);
    if (data) {
//            texture_w = width;
//            texture_h = height;
        f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        f->glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    f->glBindTexture(GL_TEXTURE_2D, 0);

    return m_textureID;;
}

std::string Utils::readShaderSource(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        assert(false);

    QTextStream in(&file);
    QString content = in.readAll();
    return content.toStdString();
}


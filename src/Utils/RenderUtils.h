//
// Created by fordchen on 2021/9/15.
//

#ifndef CFRENDERENGINE_RENDERUTILS_H
#define CFRENDERENGINE_RENDERUTILS_H

#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QSize>
#include <QImage>

#include <string>

#include "stb_image.h"
#include "stb_image_write.h"

namespace Utils {
    void saveTextureToImage(unsigned int texture, QSize size, std::string path,QOpenGLContext *context = nullptr) ;

    void saveCurrentFBOToImage(QSize size, std::string path, QOpenGLContext *context = nullptr);

    void saveFBOToImage(unsigned int fbo, QSize size, std::string path, QOpenGLContext *context = nullptr) ;

    unsigned int genTextureFromQImage( const QString &path, int* width, int* height, QOpenGLContext *context = nullptr);

    unsigned int genTextureFromStbImage(const QString &path, int* width, int* height, QOpenGLContext *context = nullptr);

    std::string readShaderSource(QString path);
}

#endif //CFRENDERENGINE_RENDERUTILS_H

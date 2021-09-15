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
    void saveTextureToImage(QOpenGLContext *context, unsigned int texture, QSize size, std::string path) ;

    void saveCurrentFBOToImage(QOpenGLContext *context, QSize size, std::string path);

    void saveFBOToImage(QOpenGLContext *context, unsigned int fbo, QSize size, std::string path) ;

    unsigned int genTextureFromQImage(QOpenGLContext *context, const QString &path);

    unsigned int genTextureFromStbImage(QOpenGLContext *context, const QString &path);
}

#endif //CFRENDERENGINE_RENDERUTILS_H

//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_TEXTURE_H
#define CFRENDERENGINE_TEXTURE_H

#include "GLResource.h"

CFENGINE_RENDER_START

class Texture : public GLResource{
public:
    Texture(unsigned int width, unsigned int height);
    Texture(QString path);

    void setHandle(unsigned int value);
    void use(int unit);
    void release() override;

public:
    int texture_width_;
    int texture_height_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_TEXTURE_H

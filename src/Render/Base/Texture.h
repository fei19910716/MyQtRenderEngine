//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_TEXTURE_H
#define CFRENDERENGINE_TEXTURE_H

#include "GLResource.h"

namespace render{

class Texture : public GLResource{
public:
    Texture(unsigned int width, unsigned int height);
    Texture(QString path);

    void setHandle(unsigned int value);
    void use(int unit);
    ~Texture();

public:
    int texture_width_;
    int texture_height_;
};

}
#endif //CFRENDERENGINE_TEXTURE_H

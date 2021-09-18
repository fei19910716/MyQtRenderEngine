//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_CFSHADERPROGRAM_H
#define CFRENDERENGINE_CFSHADERPROGRAM_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "GLResource.h"

CFENGINE_RENDER_START

class ShaderProgram: public GLResource {
public:
    ShaderProgram(std::string vertex, std::string fragment, bool fromPath = true);

    void fromSource(std::string vertexShaderSource, std::string fragmentShaderSource);
    void fromPath(std::string vertexPath, std::string fragmentPath);

    void use();
    void release() override;
    /**
     * TODO 移到renderer中
     */
    void clearColor();



    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

    void setVec2(const std::string &name, const std::vector<float> &value);
    void setVec2(const std::string &name, float x, float y);

    void setVec3(const std::string &name, const std::vector<float> &value);
    void setVec3(const std::string &name, float x, float y, float z);

    void setVec4(const std::string &name, const std::vector<float> &value);
    void setVec4(const std::string &name, float x, float y, float z, float w);

    void setMat2(const std::string &name, const std::vector<float> &value);
    void setMat3(const std::string &name, const std::vector<float> &value);
    void setMat4(const std::string &name, float* value, unsigned int count);

    void setTexture2D(const std::string &name, int textureUnit);


    std::string id_;
private:
    void checkCompileErrors(unsigned int shader, std::string type);

};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_CFSHADERPROGRAM_H

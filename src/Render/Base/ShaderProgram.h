//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_CFSHADERPROGRAM_H
#define CFRENDERENGINE_CFSHADERPROGRAM_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <QMatrix4x4>

#include "GLResource.h"
#include "Core/glm.h"

namespace render{

    /**
    * 1、如果设置了mat uniform，但是没有传值，会导致渲染空白
    * 2、如果设置了color uniform，但是没有传值，会导致黑屏
    * 2、如果给uniform传递了数值，但是类型不对，会导致黑屏（比如vec3，传递了vec4)
    */

class ShaderProgram: public GLResource {
public:
    ShaderProgram(std::string vertex, std::string fragment, bool fromPath = true);

    void fromSource(std::string vertexShaderSource, std::string fragmentShaderSource);
    void fromPath(std::string vertexPath, std::string fragmentPath);

    void use();
    ~ShaderProgram();
    /**
     * TODO 移到renderer中
     */
    void clearColor();


    void setBool(const std::string &name, bool value) ;
// ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) ;
// ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) ;
// ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) ;
    void setVec2(const std::string &name, float x, float y) ;
// ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) ;
    void setVec3(const std::string &name, float x, float y, float z) ;
// ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) ;
    void setVec4(const std::string &name, float x, float y, float z, float w);
// ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) ;
// ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) ;
// ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) ;

    void setMat4(const std::string &name, const QMatrix4x4 &mat) ;

    void setTexture2D(const std::string &name, int textureUnit);


    std::string id_;
private:
    void checkCompileErrors(unsigned int shader, std::string type);

};

}
#endif //CFRENDERENGINE_CFSHADERPROGRAM_H

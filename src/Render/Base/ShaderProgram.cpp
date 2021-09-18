//
// Created by fordchen on 2021/9/14.
//

#include "ShaderProgram.h"
#include <QDebug>

CFEngineRender::ShaderProgram::ShaderProgram(std::string vertex, std::string fragment, bool fromPath): GLResource(){
    if(fromPath)
        this->fromPath(vertex,fragment);
    else
        this->fromSource(vertex,fragment);
}

void CFEngineRender::ShaderProgram::fromPath(std::string vertexPath, std::string fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    handle_ = glCreateProgram();
    glAttachShader(handle_, vertex);
    glAttachShader(handle_, fragment);
    glLinkProgram(handle_);
    checkCompileErrors(handle_, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void CFEngineRender::ShaderProgram::fromSource(std::string vertexShaderSource, std::string fragmentShaderSource) {

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vss = vertexShaderSource.data();
    glShaderSource(vertexShader, 1, &vss, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fss = fragmentShaderSource.data();
    glShaderSource(fragmentShader, 1, &fss, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    handle_ = glCreateProgram();
    glAttachShader(handle_, vertexShader);
    glAttachShader(handle_, fragmentShader);
    glLinkProgram(handle_);
    // check for linking errors
    glGetProgramiv(handle_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(handle_, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void CFEngineRender::ShaderProgram::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void CFEngineRender::ShaderProgram::use() {
    glUseProgram(handle_);
}


void CFEngineRender::ShaderProgram::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(handle_, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(handle_, name.c_str()), value);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(handle_, name.c_str()), value);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value)
{
    glUniform2fv(glGetUniformLocation(handle_, name.c_str()), 1, &value[0]);
}
void CFEngineRender::ShaderProgram::setVec2(const std::string &name, float x, float y)
{
    glUniform2f(glGetUniformLocation(handle_, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value)
{
    glUniform3fv(glGetUniformLocation(handle_, name.c_str()), 1, &value[0]);
}
void CFEngineRender::ShaderProgram::setVec3(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(handle_, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value)
{
    glUniform4fv(glGetUniformLocation(handle_, name.c_str()), 1, &value[0]);
}
void CFEngineRender::ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(handle_, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat)
{
    glUniformMatrix2fv(glGetUniformLocation(handle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat)
{
    glUniformMatrix3fv(glGetUniformLocation(handle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void CFEngineRender::ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(handle_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void CFEngineRender::ShaderProgram::setTexture2D(const std::string &name, int textureUnit) {
    GLCALL(glUniform1i(glGetUniformLocation(handle_, name.c_str()), textureUnit))
}

void CFEngineRender::ShaderProgram::clearColor() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

CFEngineRender::ShaderProgram::~ShaderProgram() {
    glDeleteProgram(handle_);
    handle_=0;
}



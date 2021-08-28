#pragma once

#include <string>
#include <iostream>

#include <QOpenGLFunctions_3_3_Core>

class Appearance: public QOpenGLFunctions_3_3_Core {
public:
    virtual void render(float dt) {};

    virtual unsigned int createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource){
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
        unsigned int m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader);
        glAttachShader(m_program, fragmentShader);
        glLinkProgram(m_program);
        // check for linking errors
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return m_program;
    }
};
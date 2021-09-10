//
// Created by fordchen on 2021/8/30.
//

#include "TriangleSystem.h"


#include "stb_image_write.h"


void TriangleSystem::update(entt::registry &registry, float dt){
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int shaderProgram = createShaderProgram(m_vertexShader,m_fragmentShader);
    auto view = registry.view<const Triangle>();
    view.each([&](const auto &triangle){
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangle.vertices.size(), triangle.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * triangle.indices.size(), triangle.indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
//! 线框模式
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

//! 调试用，保存渲染结果
//        unsigned char * data1 = new unsigned char[400*600*4];
//        // transfer the bind fbo image data, here is the opengl result data
//        glReadPixels(0,0,400,600,GL_RGBA,GL_UNSIGNED_BYTE,data1);
//        stbi_write_png("D:\\GameEngine\\CFRenderEngine\\out1.png",400,600,4,data1,0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);
    });
}
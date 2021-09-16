//
// Created by fordchen on 2021/8/30.
//

#include "TriangleSystem.h"

#include <QDebug>

#include "stb_image_write.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/VertexBuffer.h"
#include "Render/Base/IndexBuffer.h"
#include "Render/Base/VertexArray.h"
#include "Render/Base/Texture.h"
#include "Render/Base/RenderBuffer.h"

#include "Render/Renderer/SimpleRenderer.h"

std::shared_ptr<CFEngineRender::Renderer> CFEngineRender::TriangleSystem::update(entt::registry &registry, float dt){
    initializeOpenGLFunctions();

    auto renderer_  = std::make_shared<CFEngineRender::SimpleRenderer>();

    auto shaderProgram = std::make_shared<CFEngineRender::ShaderProgram>(m_vertexShader,m_fragmentShader,false);

    shaderProgram->clearColor();
    renderer_->setShaderProgram(shaderProgram);

    auto view = registry.view<CFEngineRender::Triangle>();
    for(auto entity: view) {
        auto &triangle = view.get<CFEngineRender::Triangle>(entity);

        if(!triangle.enable()) continue;

        auto vao = std::make_shared<CFEngineRender::VertexArray>();
        auto vertexBuffer = std::make_shared<CFEngineRender::VertexBuffer>(triangle.vertices);
        auto indexBuffer = std::make_shared<CFEngineRender::IndexBuffer>(triangle.indices);

        vao->bindVertexBuffer(vertexBuffer);
        vao->bindIndexBuffer(indexBuffer);
//! 线框模式
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        shaderProgram->use();
        vao->use();
        shaderProgram->setVec4("u_color",1.0,0.0,0.0,1.0);

        renderer_->setVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


//        vao->release();
//        vertexBuffer->release();
//        indexBuffer->release();
//        shaderProgram->release();
    }
    return renderer_;
}

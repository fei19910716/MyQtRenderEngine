#include "QuadSystem.h"
#include <QDebug>
#include <QFile>

#include "stb_image_write.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/VertexBuffer.h"
#include "Render/Base/IndexBuffer.h"
#include "Render/Base/VertexArray.h"

#include "Render/Renderer/SimpleRenderer.h"
#include "Utils/RenderUtils.h"

std::shared_ptr<CFEngineRender::Renderer> CFEngineRender::QuadSystem::update(entt::registry &registry, float dt) {

    auto renderer_  = std::make_shared<CFEngineRender::SimpleRenderer>();

    auto vert = Utils::readShaderSource(vertexShader_);
    auto frag = Utils::readShaderSource(fragmentShader_);
    auto shaderProgram = std::make_shared<CFEngineRender::ShaderProgram>(vert,frag,false);
    shaderProgram->clearColor();
    renderer_->setShaderProgram(shaderProgram);

    auto view = registry.view<CFEngineRender::Quad>();
    for(auto entity: view) {
        auto &quad = view.get<CFEngineRender::Quad>(entity);

        if(!quad.enable()) continue;

        auto vao = std::make_shared<CFEngineRender::VertexArray>();
        auto vertexBuffer = std::make_shared<CFEngineRender::VertexBuffer>(quad.vertices);
        auto indexBuffer = std::make_shared<CFEngineRender::IndexBuffer>(quad.indices);

        vao->bindVertexBuffer(vertexBuffer);
        vao->bindIndexBuffer(indexBuffer);
        //! 线框模式
        //         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        shaderProgram->use();
        vao->use();
        shaderProgram->setVec4("u_color",0.0,1.0,0.0,1.0);

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

CFEngineRender::QuadSystem::QuadSystem(): System() {

}

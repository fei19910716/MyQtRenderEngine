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

namespace render{
std::shared_ptr<Renderer> QuadSystem::update(entt::registry &registry, float dt) {

    auto view = registry.view<Quad>();
    for(auto entity: view) {
        auto &quad = view.get<Quad>(entity);

        if(!quad.enable()) continue;
        auto renderer_  = std::make_shared<SimpleRenderer>();

        auto vert = Utils::readShaderSource(vertexShader_);
        auto frag = Utils::readShaderSource(fragmentShader_);
        auto shaderProgram = std::make_shared<ShaderProgram>(vert,frag,false);
        shaderProgram->clearColor();
        shaderProgram->id_ = "primitive";
        renderer_->setShaderProgram(shaderProgram);

        auto vao = std::make_shared<VertexArray>();
        auto vboLayout = std::make_shared<VertexLayout>();
        vboLayout->begin().add(Attribute::Enum::Position,3,AttribType::Enum::Float)
                .add(Attribute::Enum::Color,3,AttribType::Enum::Float)
                .end();

        auto vertexBuffer = std::make_shared<VertexBuffer>(quad.vertices,vboLayout);
        auto indexBuffer = std::make_shared<IndexBuffer>(quad.indices);

        vao->bindVertexBuffer(vertexBuffer);
        vao->bindIndexBuffer(indexBuffer);

        vao->id_ = "primitive";
        renderer_->setVertexArray(vao);
        //! 线框模式
        //         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        shaderProgram->use();

        shaderProgram->setVec3("u_color",1.0,0.0,0.0);
        glm::mat4 trans = glm::mat4(1.0f);
        shaderProgram->setMat4("m_model",trans);
        return renderer_;
    }
    return nullptr;
}

QuadSystem::QuadSystem(): System() {

}
}
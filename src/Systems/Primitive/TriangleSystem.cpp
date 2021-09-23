#include "TriangleSystem.h"

#include <QDebug>
#include <QTime>

#include "stb_image_write.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/VertexBuffer.h"
#include "Render/Base/IndexBuffer.h"
#include "Render/Base/VertexArray.h"
#include "Render/Base/Texture.h"
#include "Render/Base/RenderBuffer.h"

#include "Render/Renderer/SimpleRenderer.h"
#include "Utils/RenderUtils.h"
#include "Core/glm.h"

CFENGINE_RENDER_START
std::shared_ptr<Renderer> TriangleSystem::update(entt::registry &registry, float dt){

    auto view = registry.view<Triangle>();
    for(auto entity: view) {
        auto &triangle = view.get<Triangle>(entity);

        if(!triangle.enable()) continue;

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

        auto vertexBuffer = std::make_shared<VertexBuffer>(triangle.vertices,vboLayout);
        auto indexBuffer = std::make_shared<IndexBuffer>(triangle.indices);

        vao->bindVertexBuffer(vertexBuffer);
        vao->bindIndexBuffer(indexBuffer);

        vao->id_ = "primitive";
        renderer_->setVertexArray(vao);
//! 线框模式
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        shaderProgram->use();
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.1f, 0.1f, 0.0f));
        trans = glm::rotate(trans, glm::radians(10.0f), glm::vec3(0.0, 0.0, 1.0));
        shaderProgram->setVec3("u_color",glm::vec3(0.6,0.3,0.2));
        shaderProgram->setMat4("m_model",trans);

        return renderer_;
    }
    return nullptr;
}

TriangleSystem::TriangleSystem():System() {

}
CFENGINE_RENDER_END
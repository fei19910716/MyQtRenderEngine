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

#include "Components/Primitive/Triangle.h"
#include "Components/Base/Transform.h"

namespace render{
std::shared_ptr<Renderer> TriangleSystem::update(entt::registry &registry, float dt){

    auto view = registry.view<Triangle,Transform>();
    for(auto entity: view) {
        auto &triangle = view.get<Triangle>(entity);
        auto &transform = view.get<Transform>(entity);

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

        trans = glm::translate(trans, transform.position());
        trans = glm::rotate(trans, glm::radians(transform.rotation().x), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(transform.rotation().y), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(transform.rotation().z), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, transform.scale());
        shaderProgram->setVec3("u_color",glm::vec3(0.6,0.3,0.2));
        shaderProgram->setMat4("m_model",trans);

        return renderer_;
    }
    return nullptr;
}

TriangleSystem::TriangleSystem():System() {

}
}
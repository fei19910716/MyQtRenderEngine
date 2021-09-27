//
// Created by fordchen on 2021/9/27.
//

#include "CubeSystem.h"

#include "Components/Primitive/Cube.h"
#include "Components/Base/Transform.h"

#include "Render/Renderer/SimpleRenderer.h"
#include "Render/Base/VertexArray.h"
#include "Render/Base/VertexBuffer.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/IndexBuffer.h"

#include "Utils/RenderUtils.h"
namespace render{
    std::shared_ptr<Renderer> CubeSystem::update(entt::registry &registry, float dt){

        auto view = registry.view<Cube,Transform>();
        for(auto entity: view) {
            auto &cube = view.get<Cube>(entity);
            auto &transform = view.get<Transform>(entity);

            if(!cube.enable()) continue;

            auto renderer_  = std::make_shared<SimpleRenderer>();

            auto vert = Utils::readShaderSource(vertexShader_);
            auto frag = Utils::readShaderSource(fragmentShader_);
            auto shaderProgram = std::make_shared<ShaderProgram>(vert,frag,false);
            shaderProgram->clearColor();
            shaderProgram->id_ = "cube";
            renderer_->setShaderProgram(shaderProgram);

            auto vao = std::make_shared<VertexArray>();
            auto vboLayout = std::make_shared<VertexLayout>();
            vboLayout->begin().add(Attribute::Enum::Position,3,AttribType::Enum::Float)
                              .end();

            auto vertexBuffer = std::make_shared<VertexBuffer>(cube.vertices,vboLayout);
            auto indexBuffer = std::make_shared<IndexBuffer>(cube.indices);

            vao->bindVertexBuffer(vertexBuffer);
            vao->bindIndexBuffer(indexBuffer);

            vao->id_ = "cube";
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
}

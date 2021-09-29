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
#include "Render/Common/CameraManager.h"

#include "Components/Primitive/Triangle.h"
#include "Components/Base/Transform.h"
#include "Components/Base/Camera.h"


namespace render{
std::shared_ptr<Renderer> TriangleSystem::update(entt::registry &registry, float dt){

    auto renderer_  = std::make_shared<SimpleRenderer>();
    std::shared_ptr<ShaderProgram> shaderProgram;

    auto triangle_view = registry.view<Triangle>();
    for(auto entity: triangle_view) {
        auto &triangle = triangle_view.get<Triangle>(entity);
        auto transform = ENTT::registry.get<Transform>(entity);

        if(!triangle.enable()) continue;

        auto vert = Utils::readShaderSource(vertexShader_);
        auto frag = Utils::readShaderSource(fragmentShader_);
        shaderProgram = std::make_shared<ShaderProgram>(vert,frag,false);
        shaderProgram->clearColor();
        shaderProgram->id_ = "primitive";
        renderer_->setShaderProgram(shaderProgram);

        shaderProgram->use();


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

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, transform.position());
        trans = glm::rotate(trans, glm::radians(transform.rotation().x), glm::vec3(1.0, 0.0, 0.0));
        trans = glm::rotate(trans, glm::radians(transform.rotation().y), glm::vec3(0.0, 1.0, 0.0));
        trans = glm::rotate(trans, glm::radians(transform.rotation().z), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, transform.scale());
        shaderProgram->setMat4("m_model",trans);
    }

    if(!shaderProgram)
        return renderer_;

    auto camera_view = registry.view<Camera>();
    for(auto entity: camera_view) {
        auto camera = camera_view.get<Camera>(entity);

        if(!camera.enable()) continue;

        glm::mat4 projection = glm::perspective(glm::radians(camera.fov()), camera.aspect(), camera.near(), camera.far());
        shaderProgram->setMat4("m_projection", projection);


        auto view = CameraManager::Inst()->GetViewMatrix();
        shaderProgram->setMat4("m_view", view);

        shaderProgram->setVec3("u_color",glm::vec3(0.6,0.3,0.2));
    }

    return renderer_;
}
}
//
// Created by fordchen on 2021/9/14.
//

#include "SimpleRenderer.h"

#include <iostream>

#include "Render/Base/VertexArray.h"
#include "Render/Base/VertexBuffer.h"
#include "Render/Base/IndexBuffer.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/Texture.h"
#include "Utils/RenderUtils.h"

#include "Render/Common/engine_common.h"

CFEngineRender::SimpleRenderer::SimpleRenderer()
        : Renderer(),
          GL()
//          shader_(nullptr),
//          vao_(nullptr)
{
    auto vao = std::make_shared<CFEngineRender::VertexArray>();
    auto vboLayout = std::make_shared<VertexLayout>();
    vboLayout->begin().add(Attribute::Enum::Position,3,AttribType::Enum::Float)
            .add(Attribute::Enum::TextureCoord,2,AttribType::Enum::Float)
            .end();

    auto vertexBuffer = std::make_shared<CFEngineRender::VertexBuffer>(CFEngineRender::SIMPLE_VERTEX,vboLayout);
    auto indexBuffer = std::make_shared<CFEngineRender::IndexBuffer>(CFEngineRender::SIMPLE_INDEX);

    vao->bindVertexBuffer(vertexBuffer);
    vao->bindIndexBuffer(indexBuffer);

    vao->id_ = "simple";

    vao_.push_back(vao);

    auto vert = Utils::readShaderSource(":/shader/simple/simple.vert");
    auto frag = Utils::readShaderSource(":/shader/simple/simple.frag");
    auto shaderProgram = std::make_shared<CFEngineRender::ShaderProgram>(vert,frag,false);

    shaderProgram->id_ = "simple";
    shader_.push_back(shaderProgram);
}

CFEngineRender::SimpleRenderer::SimpleRenderer(const std::string &vertex_shader, const std::string &fragment_shader)
        : Renderer(),
          GL()
//          shader_(nullptr),
//          vao_(nullptr)
{
    initializeOpenGLFunctions();
    auto vao = std::make_shared<CFEngineRender::VertexArray>();
    auto vboLayout = std::make_shared<VertexLayout>();
    vboLayout->begin().add(Attribute::Enum::Position,3,AttribType::Enum::Float)
            .add(Attribute::Enum::TextureCoord,2,AttribType::Enum::Float)
            .end();

    auto vertexBuffer = std::make_shared<CFEngineRender::VertexBuffer>(CFEngineRender::SIMPLE_VERTEX,vboLayout);
    auto indexBuffer = std::make_shared<CFEngineRender::IndexBuffer>(CFEngineRender::SIMPLE_INDEX);

    vao->bindVertexBuffer(vertexBuffer);
    vao->bindIndexBuffer(indexBuffer);

    vao_.push_back(vao);

    auto vert = Utils::readShaderSource(":/shader/simple/simple.vert");
    auto frag = Utils::readShaderSource(":/shader/simple/simple.frag");
    auto shaderProgram = std::make_shared<CFEngineRender::ShaderProgram>(vert,frag,false);
    shader_.push_back(shaderProgram);
}

CFEngineRender::SimpleRenderer::~SimpleRenderer() {}

bool CFEngineRender::SimpleRenderer::init() {
    return true;
}

void CFEngineRender::SimpleRenderer::render() {
    if(vao_.empty() || shader_.empty())
        return;

    bindInput();
    bindOutput();
    renderInternal();
    postRender();
    /**
     * 调用glFinish()非常重要，否则可能画面没有渲染
     */
    glFinish();
}

/**
 * 不做后处理
 */
void CFEngineRender::SimpleRenderer::postRender() {}

void CFEngineRender::SimpleRenderer::release() {}

void CFEngineRender::SimpleRenderer::setVertexArray(std::shared_ptr<VertexArray> vertexArray) {
//    vao_ = vertexArray;
    vao_.push_back(vertexArray);
}

void CFEngineRender::SimpleRenderer::bindInput() {
    if(input_.empty()) return;

    for(int i = 0; i < input_.size(); i++){
        if (input_[i] == nullptr) continue;
        Utils::saveFBOToImage( input_[i]->handle(),QSize(400,600), "D:\\GameEngine\\CFRenderEngine\\" + this->id() + "__bindInput.png", QOpenGLContext::currentContext());

        std::string textureKey = DEFAULT_INPUT_TEXTURE_NAME;
        textureKey += std::to_string(i);
        setUniformTexture2D(textureKey,input_[i]->texture(),i);
    }
}

void CFEngineRender::SimpleRenderer::bindOutput() {
    if(output_ == nullptr){
        output_ = std::make_shared<CFEngineRender::FrameBuffer>(true); // 绑定到屏幕
    }
    output_->use();
}

void CFEngineRender::SimpleRenderer::renderInternal() {

    for(int i = 0; i < vao_.size(); i++){
        auto vao = vao_[i];
        auto shader = shader_[i];

        output_->use();
        shader->use();
        vao->use();

        GLCALL(glDrawElements(GL_TRIANGLES, vao->vertexCount(), GL_UNSIGNED_INT, 0);)
        GLCALL(glFinish();)
        Utils::saveFBOToImage( output_->handle(),QSize(400,600), "D:\\GameEngine\\CFRenderEngine\\" + shader->id_ + ".png", QOpenGLContext::currentContext());
    }

}

void CFEngineRender::SimpleRenderer::setUniformTexture2D(std::string key, std::shared_ptr<Texture> texture, int index) {
    auto shader = shader_.front();
    std::cout << "shader -----id: " <<shader->id_ << std::endl;
    shader->use();
    shader->setTexture2D(key,index);
    texture->use(index);
}

void CFEngineRender::SimpleRenderer::setUniformVec4(std::string key, std::vector<float> &value) {
    shader_.back()->setVec4(key,value);
}

void CFEngineRender::SimpleRenderer::setUniformMat4(std::string key, std::vector<float> &value) {
    shader_.back()->setMat4(key,value.data(),value.size());
}

void CFEngineRender::SimpleRenderer::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
    shader_ .push_back(shaderProgram);
}

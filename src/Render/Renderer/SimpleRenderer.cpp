//
// Created by fordchen on 2021/9/14.
//

#include "SimpleRenderer.h"

#include "Render/Base/VertexArray.h"
#include "Render/Base/ShaderProgram.h"
#include "Render/Base/Texture.h"
#include "Utils/RenderUtils.h"

CFEngineRender::SimpleRenderer::SimpleRenderer()
        : Renderer(),
          GL(),
          shader_(nullptr),
          vao_(nullptr)
{

}

CFEngineRender::SimpleRenderer::SimpleRenderer(const std::string &vertex_shader, const std::string &fragment_shader)
        : Renderer(),
          GL(),
          shader_(nullptr),
          vao_(nullptr)
{
    initializeOpenGLFunctions();
    shader_ = std::make_shared<CFEngineRender::ShaderProgram>(vertex_shader,fragment_shader,false);
}

CFEngineRender::SimpleRenderer::~SimpleRenderer() {}

bool CFEngineRender::SimpleRenderer::init() {
    return true;
}

void CFEngineRender::SimpleRenderer::render() {
    if(!shader_ || !vao_)
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
    vao_ = vertexArray;
}

void CFEngineRender::SimpleRenderer::bindInput() {
    if(input_.empty()) return;

    for(int i = 0; i < input_.size(); i++){
        if (input_[i] == nullptr) continue;
        Utils::saveFBOToImage( input_[i]->handle(),QSize(400,600), "D:\\GameEngine\\CFRenderEngine\\" + this->id() + "__.png", QOpenGLContext::currentContext());

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
    shader_->use();
    vao_->use();

    glDrawElements(GL_TRIANGLES, vao_->vertexCount(), GL_UNSIGNED_INT, 0);
    glFinish();
}

void CFEngineRender::SimpleRenderer::setUniformTexture2D(std::string key, std::shared_ptr<Texture> texture, int index) {
    shader_->use();
    shader_->setTexture2D(key,index);
    texture->use(index);
}

void CFEngineRender::SimpleRenderer::setUniformVec4(std::string key, std::vector<float> &value) {
    shader_->setVec4(key,value);
}

void CFEngineRender::SimpleRenderer::setUniformMat4(std::string key, std::vector<float> &value) {
    shader_->setMat4(key,value.data(),value.size());
}

void CFEngineRender::SimpleRenderer::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) {
    shader_ = shaderProgram;
}

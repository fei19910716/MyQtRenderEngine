#include "RenderEngine.h"

#include <QDebug>

#include "Render/Graph/RenderQueue.h"
#include "Utils/RenderUtils.h"

#include "Render/Base/RenderBuffer.h"
#include "Render/Base/FrameBuffer.h"
#include "Render/Base/Texture.h"


#include "Systems/Primitive/TriangleSystem.h"
#include "Systems/Primitive/QuadSystem.h"

namespace render{

RenderEngine::RenderEngine():textureToRender_(nullptr),textureToDisplay_(nullptr),textureToDelete_(nullptr){

    m_systems.push_back(new QuadSystem());
    m_systems.push_back(new TriangleSystem());



}

RenderEngine::~RenderEngine() noexcept {
    for(auto& item: m_systems){
        delete item;
    }

//    // 删除gl资源
//    textureToRender_->release();
//    textureToDisplay_->release();
//    rbo_->release();
//    fbo_->release();
}


void RenderEngine::update(float dt){

//    fbo_->bindTexture(textureToRender_);
//
//    fbo_->use();
//
//    if(textureToDelete_ && textureToDelete_->valid()){
//        textureToDelete_->release();
//    }

    renderQueue = std::make_shared<RenderQueue>();

    auto input = std::make_shared<FrameBuffer>();
    //auto texture = std::make_shared<Texture>("D:\\GameEngine\\CFRenderEngine\\asset\\image\\out1.png");
    auto texture = std::make_shared<Texture>(400,600);
    this->setRenderSize(texture->texture_width_,texture->texture_height_);
    input->bindRenderBuffer(std::make_shared<RenderBuffer>(width_,height_));
    input->bindTexture(texture);

    /**
     * fixme 为啥output的创建放在renderQueue的创建之前就会导致渲染空白的问题？
     */
    auto output = std::make_shared<FrameBuffer>(width_,height_);
    
    renderQueue->setInput(input);
    renderQueue->setOutput(output);
    int i = 1;
    for (System *system : m_systems) {
        renderQueue->addRenderer(system->update(ENTT::registry, dt),std::to_string( i++));
    }
    renderQueue->render();
    // Utils::saveFBOToImage( renderQueue->output()->handle(),QSize(width_,height_), "D:\\GameEngine\\CFRenderEngine\\" + renderQueue->id() + ".png", QOpenGLContext::currentContext());
//    unsigned int value = textureToDisplay_->handle();
//    textureToDisplay_->setHandle(textureToRender_->handle());
//    textureToRender_->setHandle(value);
//
//    qSwap(m_textureToDisplay, m_textureToRender);

}

void RenderEngine::setRenderSize(int width,int height){
    if(width_ == width && height_ == height){
       return;
    }
    width_ = width;
    height_ = height;
//    initializeOpenGLFunctions();

//    // 创建纹理
//    if(textureToRender_ && textureToRender_->valid()){
//        textureToRender_->release();
//    }
//    textureToDisplay_ = std::make_shared<Texture>(width,height);
//    textureToRender_ = std::make_shared<Texture>(width,height);
//
//    // 创建FBO
//    if(fbo_ && fbo_->valid()){
//        fbo_->release();
//    }
//    fbo_ = std::make_shared<FrameBuffer>();
//
//
//    // 创建rbo
//    if(rbo_ && rbo_->valid()){
//        rbo_->release();
//    }
//    rbo_ = std::make_shared<RenderBuffer>(width,height);
//
//    fbo_->bindRenderBuffer(rbo_);
//    fbo_->bindTexture(textureToRender_);
//
//    renderer_->setOutput(fbo_);
}
}
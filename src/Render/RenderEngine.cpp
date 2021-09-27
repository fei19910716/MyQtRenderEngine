#include "RenderEngine.h"

#include <QDebug>

#include "Render/Graph/RenderQueue.h"
#include "Utils/RenderUtils.h"

#include "Render/Base/RenderBuffer.h"
#include "Render/Base/FrameBuffer.h"
#include "Render/Base/Texture.h"


#include "Systems/Primitive/TriangleSystem.h"
#include "Systems/Primitive/QuadSystem.h"
#include "Systems/Primitive/CubeSystem.h"

namespace render{

RenderEngine::RenderEngine():textureToRender_(nullptr),textureToDisplay_(nullptr),textureToDelete_(nullptr){

    m_systems.push_back(std::make_shared<QuadSystem>());
    m_systems.push_back(std::make_shared<TriangleSystem>());
    m_systems.push_back(std::make_shared<CubeSystem>());
}

void RenderEngine::update(float dt){

    renderQueue = std::make_shared<RenderQueue>();

    auto input = std::make_shared<FrameBuffer>();
    input->bindRenderBuffer(std::make_shared<RenderBuffer>(render_width_,render_height_));
    input->bindTexture(std::make_shared<Texture>(render_width_,render_height_));

    /**
     * fixme 为啥output的创建放在renderQueue的创建之前就会导致渲染空白的问题？
     */
    auto output = std::make_shared<FrameBuffer>();
    output->bindRenderBuffer(std::make_shared<RenderBuffer>(render_width_,render_height_));
    output->bindTexture(textureToRender_);

    if(textureToDelete_ && textureToDelete_->valid()){
        textureToDelete_ = nullptr;
    }
    
    renderQueue->setInput(input);
    renderQueue->setOutput(output);
    int i = 1;
    for (auto& system : m_systems) {
        renderQueue->addRenderer(system->update(ENTT::registry, dt),std::to_string( i++));
    }
    renderQueue->setRenderSize(render_width_,render_height_);
    renderQueue->render();
    // Utils::saveFBOToImage( renderQueue->output()->handle(),QSize(width_,height_), "D:\\GameEngine\\CFRenderEngine\\" + renderQueue->id() + ".png", QOpenGLContext::currentContext());

    unsigned int value = textureToDisplay_->handle();
    textureToDisplay_->setHandle(textureToRender_->handle());
    textureToRender_->setHandle(value);

//    qSwap(m_textureToDisplay, m_textureToRender);

}

void RenderEngine::setRenderSize(int width,int height){
    if(render_width_ == width && render_height_ == height){
       return;
    }
    render_width_ = width;
    render_height_ = height;

    // 创建纹理
    textureToDisplay_ = std::make_shared<Texture>(width,height);
    textureToRender_ = std::make_shared<Texture>(width,height);
}
}
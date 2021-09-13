#include "RenderEngine.h"

#include <QDebug>

#include "Entity/EntityManager.h"

RenderEngine::RenderEngine():m_textureToRender(0),m_textureToDisplay(0),m_textureToDelete(0){
  ComponentManager::registerComponentDescriptions();
  m_systems.push_back(new TriangleSystem());
}

RenderEngine::~RenderEngine() noexcept {
    for(auto& item: m_systems){
        delete item;
    }

    // 删除gl资源
    if (m_textureToRender != 0) {
        glDeleteTextures(1, &m_textureToRender);
        m_textureToRender = 0;
    }
    if (m_textureToDisplay != 0) {
        glDeleteTextures(1, &m_textureToDisplay);
        m_textureToDisplay = 0;
    }
    if (m_fbo) {
        glDeleteFramebuffers(1,&m_fbo);
        m_fbo = 0;
    }
    if (m_rbo) {
        glDeleteRenderbuffers(1,&m_rbo);
        m_rbo = 0;
    }
}


void RenderEngine::update(float dt){
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glBindTexture(GL_TEXTURE_2D, m_textureToRender);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureToRender, 0);

    if(m_textureToDelete){
        glDeleteTextures(1, &m_textureToDelete);
        m_textureToDelete = 0;
    }


    for (System *system : m_systems) {
        system->update(ENTT::registry, dt);
    }
    /**
     * 调用glFinish()非常重要，否则可能画面没有渲染
     */
    glFinish();
    qSwap(m_textureToDisplay, m_textureToRender);

}

void RenderEngine::setRenderSize(int width,int height){
    if(m_width == width && m_height == height){
       return;
    }
    m_width = width;
    m_height = height;

    initializeOpenGLFunctions();

    // 创建纹理
    if(m_textureToRender){
        glDeleteTextures(1, &m_textureToRender);
        m_textureToDelete = m_textureToDisplay;
    }
    this->genNewTexture(&m_textureToDisplay,QSize(width,height));
    this->genNewTexture(&m_textureToRender,QSize(width,height));

    // 创建FBO
    if(m_fbo){
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);


    // 创建rbo
    if(m_rbo){
        glDeleteRenderbuffers(1, &m_rbo);
        m_rbo = 0;
    }
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureToRender, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    glViewport(0,0,width,height);
}

void RenderEngine::genNewTexture(GLuint* texture, QSize size) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width(), size.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
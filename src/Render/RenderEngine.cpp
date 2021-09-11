#include "RenderEngine.h"

#include "Entity/EntityManager.h"

RenderEngine::RenderEngine(){
      ComponentManager::registerComponentDescriptions();
      m_systems.push_back(new TriangleSystem());
  }

void RenderEngine::update(float dt){
    for (System *system : m_systems) {
        system->update(EntityManager::m_registry, dt);
    }

    unsigned int tmp = m_textureToRender;
    m_textureToRender = m_textureToDisplay;
    m_textureToDisplay = tmp;
}

void RenderEngine::setRenderSize(int width,int height){
    if(m_width == width && m_height == height){
       return;
    }
    m_width = width;
    m_height = height;

    initializeOpenGLFunctions();

    // 创建纹理
    glGenTextures(1, &m_textureToDisplay);
    glBindTexture(GL_TEXTURE_2D, m_textureToDisplay);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 创建FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    // 创建纹理
    glGenTextures(1, &m_textureToRender);
    glBindTexture(GL_TEXTURE_2D, m_textureToRender);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 创建rbo
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureToRender, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    glViewport(0,0,width,height);
}
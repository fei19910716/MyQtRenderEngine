#include "renderthread.h"
#include <iostream>

#include <QDateTime>

#include "Utils/RenderUtils.h"
#include "Render/Graph/RenderQueue.h"

#include "Render/Base/Texture.h"

namespace render{
RenderThread::~RenderThread() {

}

void RenderThread::release() {
    m_renderContext->makeCurrent(m_renderSurface);
    delete m_renderEngine;
    delete m_renderSurface;
    m_renderContext->doneCurrent();
    delete m_renderContext;
    exit(0);
}

RenderThread::RenderThread(QOffscreenSurface *surface, QOpenGLContext *context,QObject* parent):
    QThread (parent),
    m_renderSurface(surface),
    m_mainContext(context)

{
    m_renderContext = new QOpenGLContext;
    m_renderContext->setFormat(m_mainContext->format());
    m_renderContext->setShareContext(m_mainContext);
    m_renderContext->create();
    m_renderContext->moveToThread(this);

    // TODO 在RenderEngine的构造函数中会调用gl函数，如果在这里构造m_renderEngine会导致initializeOpenGLFunctions()失败，因为线程还没有构造成功，因此该线程没有context，需要移到run函数
    // m_renderEngine=new RenderEngine;

}

void RenderThread::run(){

    m_renderContext->makeCurrent(m_renderSurface);

    m_renderEngine=new RenderEngine;
    TextureBuffer::instance()->createTexture(m_renderContext);
    while (m_running){
        if(!m_requestRender){
            QMutexLocker lock(&m_mutex);
            m_condition.wait(&m_mutex);
        }
        m_renderContext->functions()->glViewport(0,0,render_width_,render_height_);
        m_renderEngine->setRenderSize(render_width_, render_height_);
        m_renderEngine->update(QDateTime::currentDateTime().time().msec());

        // m_renderContext->functions()->glBindFramebuffer(GL_FRAMEBUFFER,m_renderEngine->renderQueue->output()->handle()); // TODO 这里需要绑定最终的输出FBO到context上
        m_renderEngine->renderQueue->output()->use();
        TextureBuffer::instance()->updateTexture(m_renderContext,m_renderEngine->textureToDisplay_->handle());
        // TextureBuffer::instance()->updateTexture(m_renderContext,render_width_,render_height_); // TODO 使用深拷贝texture时，createTexture必须要调用
        emit imageReady();
        m_requestRender = false;
    }
    TextureBuffer::instance()->deleteTexture(m_renderContext);
}

void RenderThread::setRenderSize(int width, int height)
{
    QMutexLocker lock(&m_mutex);
    render_width_ = width;
    render_height_ = height;
}
}
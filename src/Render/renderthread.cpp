#include "renderthread.h"
#include <iostream>

#include <QDateTime>

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
    m_renderSurface->moveToThread(this);
}

void RenderThread::run(){

    m_renderContext->makeCurrent(m_renderSurface);
    if(m_renderEngine== nullptr){
        m_renderEngine=new RenderEngine;
    }
    TextureBuffer::instance()->createTexture(m_renderContext);
    while (m_running){
        if(!m_requestRender){
            static QMutex lock_;
            QMutexLocker lock(&lock_);
            m_condition.wait(&lock_);
        }
        m_renderEngine->setRenderSize(m_width, m_height);
        m_renderEngine->update(QDateTime::currentDateTime().time().msec());

        // TextureBuffer::instance()->updateTexture(m_renderContext,m_width,m_height);
        TextureBuffer::instance()->updateTexture(m_renderContext,m_renderEngine->m_textureToDisplay);
        emit imageReady();
        m_requestRender = false;
    }
    TextureBuffer::instance()->deleteTexture(m_renderContext);
}

void RenderThread::setRenderSize(int width, int height)
{
    QMutexLocker lock(&m_mutex);
    m_width = width;
    m_height = height;
}

RenderThread::~RenderThread() {

}

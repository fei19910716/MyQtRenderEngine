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

}

void RenderThread::run(){

    m_renderContext->makeCurrent(m_renderSurface);
    if(m_renderEngine== nullptr){
        m_renderEngine=new RenderEngine;
    }
    TextureBuffer::instance()->createTexture(m_renderContext);
    int width = 0, height = 0;
    while (m_running){
        {
            QMutexLocker lock(&m_mutex);
            width = m_width;
            height = m_height;
        }
        m_renderEngine->setRenderSize(width, height);
        m_renderEngine->update(QDateTime::currentDateTime().time().msec());

        TextureBuffer::instance()->updateTexture(m_renderContext,width,height);
        emit imageReady();

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

    m_running = false;
    this->wait();
}

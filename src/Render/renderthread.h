#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QObject>
#include <QThread>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMutex>
#include <QWaitCondition>

#include "RenderEngine.h"
#include "TextureBuffer.h"

class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(QOffscreenSurface* surface,QOpenGLContext* context,QObject* parent=nullptr);
    ~RenderThread();

    void setRenderSize(int width, int height);
    void run() override;
    void setRenderDegree(float degree);

    /**
     * 释放gl资源，只能在本线程调用
     */
    Q_INVOKABLE void release();

signals:
    void imageReady();

public:
    RenderThread(const RenderThread &) = delete;
    RenderThread &operator =(const RenderThread &) = delete;
    RenderThread(const RenderThread &&) = delete;
    RenderThread &operator =(const RenderThread &&) = delete;

    QOffscreenSurface* m_renderSurface;
    QOpenGLContext* m_renderContext;
    QOpenGLContext* m_mainContext;
    QMutex m_mutex;
    QWaitCondition m_condition;
    unsigned int m_width;
    unsigned int m_height;
    bool  m_running = true;
    bool m_requestRender = false;
    RenderEngine* m_renderEngine= nullptr;
};

#endif // RENDERTHREAD_H

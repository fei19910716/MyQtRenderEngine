#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QMutex>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "Render/renderthread.h"

class RenderView : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit RenderView(QWidget *parent = nullptr);
    /**
     * 资源清理：子线程和本线程的gl资源
     */
    ~RenderView();

signals:

public slots:

public:
    void initializeGL();

protected:
    void wheelEvent(QWheelEvent *event) override;

public:
    void resizeGL(int w, int h);
    void paintGL();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

public:
    void initRenderThread();

    void requestRender();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    /**
     * UI线程的context，子线程需要与之share
     */
    QOpenGLContext* m_context;

    /**
     * UI线程渲染的ShaderProgram
     */
    QOpenGLShaderProgram* m_program;

    /**
     * 仅Debug用。UI线程渲染的纹理，用于渲染一张图片
     */
    unsigned int m_textureID;

    /**
     * 仅Debug用。加载图片的宽高
     */
    int texture_w;
    int texture_h;

    /**
     * UI线程渲染的VAO
     */
    unsigned int m_vao;


    /**
     * 渲染子线程，离屏渲染后共享纹理给UI线程上屏
     */
    render::RenderThread* m_thread=nullptr;

    QMutex lock_;

    float mx = 0,my = 0,ax = 0,ay = 0;
    bool isDown = false;
};

#endif // RENDERVIEW_H

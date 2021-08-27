#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

#include "Render/renderthread.h"
class RenderView : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit RenderView(QWidget *parent = nullptr);

signals:

public slots:

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void initRenderThread();
    void genTextureFromImage(const QString& path);
    void genTextureFromStb_image(const QString& path);

private:
    QOpenGLContext* m_context;
    QOpenGLShaderProgram* m_program;
    unsigned int m_textureID;
    unsigned int m_vao;
    int texture_w;
    int texture_h;
    RenderThread* m_thread=nullptr;
};

#endif // RENDERVIEW_H

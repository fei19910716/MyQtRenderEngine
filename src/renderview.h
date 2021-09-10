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
    void genTextureFromQImage(const QString& path);
    void genTextureFromStbImage(const QString& path);
    void saveFBOToPNG(QString& path);

private:
    QOpenGLContext* m_context;
    QOpenGLShaderProgram* m_program;
    unsigned int m_textureID;
    unsigned int m_vao;
    int texture_w;
    int texture_h;
    RenderThread* m_thread=nullptr;

    const int WIDTH = 400;
    const int HEIGHT = 600;
};

#endif // RENDERVIEW_H

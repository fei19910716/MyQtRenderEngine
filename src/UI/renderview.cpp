#include "renderview.h"
#include <QDebug>
#include <QMouseEvent>

#include "Entity/EntityManager.h"
#include "Utils/RenderUtils.h"
#include "Render/Common/engine_common.h"
#include "Core/entityx.h"
#include "Core/CameraManager.h"
#include "Components/Base/Camera.h"


Q_DECLARE_METATYPE(glm::vec2)

RenderView::RenderView(QWidget *parent) : QOpenGLWidget(parent)
{

}

RenderView::~RenderView(){
    // 清除子线程的资源
    m_thread->m_running = false;
    m_thread->m_condition.wakeAll();
    QMetaObject::invokeMethod(m_thread,"release",Qt::QueuedConnection);
    m_thread->wait();

    // 清除本线程的资源
    auto context = this->context();
    auto mainSurface = context->surface();
    context->makeCurrent(mainSurface);
    delete m_program;
    m_program = nullptr;
    context->doneCurrent();

}

void RenderView::initializeGL()
{
    initRenderThread();
    if(!initializeOpenGLFunctions()){
        qDebug() << "initializeOpenGLFunctions fail!";
    }

    glViewport(0, 0, width(), height());

    m_program=new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,Utils::readShaderSource(":/shader/simple/simple.vert").c_str());
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,Utils::readShaderSource(":/shader/simple/simple.frag").c_str());
    m_program->link();

    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);

    GLuint vbo,ebo;
    glGenBuffers(1,&vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * render::SIMPLE_VERTEX.size(), render::SIMPLE_VERTEX.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * render::SIMPLE_INDEX.size(), render::SIMPLE_INDEX.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    {
        //! 调试用，加载纹理
        // m_textureID = Utils::genTextureFromStbImage("D:\\GameEngine\\CFRenderEngine\\asset\\image\\test.png", &texture_w, &texture_h,this->context());
    }

    glBindVertexArray(0);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_thread->setRenderSize(this->width(), this->height());
    this->requestRender();
}

void RenderView::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void RenderView::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    glBindVertexArray(m_vao);

    {
        //! 调试用，渲染一张图片
//        glBindTexture(GL_TEXTURE_2D, m_textureID);
//        glActiveTexture(GL_TEXTURE0);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        Utils::saveTextureToImage(this->context(),m_textureID,QSize(texture_w,texture_h),"D:\\GameEngine\\CFRenderEngine\\test_out.png"); // TODO 为什么这句中的f->glGetTexImage会crash？ 而下一句中不会crash？ ans: 因为传入的size和图片的size不一致
    }

    render::TextureBuffer::instance()->drawTexture(this->context(), 6);

    glBindVertexArray(0);
    m_program->release();

}

void RenderView::requestRender() {
    m_thread->m_condition.wakeOne();
}

void RenderView::initRenderThread()
{
    qDebug()<<"GLWidget::initRenderThread() start.";
    auto context = this->context();
    auto mainSurface = context->surface();

    auto renderSurface = new QOffscreenSurface(nullptr);
    renderSurface->setFormat(mainSurface->format());
    renderSurface->create();

    context->doneCurrent();
    m_thread = new render::RenderThread(renderSurface,context,this);
    context->makeCurrent(mainSurface);

    connect(m_thread,&render::RenderThread::imageReady, this, [this]() { update(); },Qt::QueuedConnection);
    m_thread->setRenderSize(this->width(),this->height());
    m_thread->start();

    qDebug() << "GLWidget::initRenderThread() end";
}

void RenderView::mousePressEvent(QMouseEvent *event) {
    lastX = event->x();
    lastY = event->y();
}

void RenderView::mouseReleaseEvent(QMouseEvent *event) {

}

void RenderView::mouseMoveEvent(QMouseEvent *event) {

    if(event->buttons() & Qt::LeftButton){
        float xoffset = lastX - event->x();
        float yoffset = event->y() - lastY; // reversed since y-coordinates go from bottom to top

        lastX = event->x();
        lastY = event->y();


        CameraManager::instance()->ProcessMouseMovement(xoffset, yoffset);
        this->requestRender();
    } else{ // 旋转

    }
}

void RenderView::wheelEvent(QWheelEvent *event) {
    float delta = event->delta() > 0 ? 5.0f : -5.0f;
    CameraManager::instance()->ProcessMouseScroll(delta);
    this->requestRender();

}

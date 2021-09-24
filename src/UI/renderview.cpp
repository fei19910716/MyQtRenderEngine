#include "renderview.h"
#include <QDebug>

#include "Entity/EntityManager.h"
#include "Utils/RenderUtils.h"

static float vertices[] = {
//     ---- 位置 ----           - 纹理坐标 -
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
};

static unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
};

static const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "    TexCoord = aTexCoord;\n"
        "}\n";
static const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(ourTexture, TexCoord);\n"
        "}\n";

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
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShaderSource);
    m_program->link();

    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);

    GLuint vbo,ebo;
    glGenBuffers(1,&vbo);
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
}

void RenderView::resizeGL(int w, int h)
{
    m_thread->setRenderSize(w, h);
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
    QMutexLocker locker(&lock_);
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
    m_thread->start();

    qDebug() << "GLWidget::initRenderThread() end";
}

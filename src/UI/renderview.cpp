#include "renderview.h"
#include <QDebug>

#include "Entity/EntityManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

static float vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     1.0f,  0.8f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     1.0f, -0.8f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -1.0f, -0.8f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -1.0f,  0.8f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

static unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

static const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "    TexCoord = aTexCoord;\n"
        "}\n";
static const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(ourTexture, TexCoord);\n"
        "}\n";

RenderView::RenderView(QWidget *parent) : QOpenGLWidget(parent)
{

}

void RenderView::onAddEntity(){
    EntityManager::createEntity(1);
    Q_EMIT rebuildObejctTree();
}

void RenderView::onDelEntity(){
    EntityManager::deleteEntity(1);
    Q_EMIT rebuildObejctTree();
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //! 加载纹理
    genTextureFromStbImage("D:\\GameEngine\\CFRenderEngine\\test.png");

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
    glClearColor(0.7f,0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    glBindVertexArray(m_vao);
//! 调试用，渲染一张图片
//    glBindTexture(GL_TEXTURE_2D, m_textureID);
//    glActiveTexture(GL_TEXTURE0);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    TextureBuffer::instance()->drawTexture(this->context(), 6);

    glBindVertexArray(0);
    m_program->release();

}

void RenderView::saveFBOToPNG(QString& path){
    //! save the opengl result to image
     unsigned char * data1 = new unsigned char[width()*height()*4];
     glReadPixels(0,0,width(),height(),GL_RGBA,GL_UNSIGNED_BYTE,data1);
     stbi_write_png("",width(),height(),4,data1,0);

    // save the texture to image, we should first bind it to a fbo
//    GLuint fbo;
//    glGenFramebuffers(1, &fbo);
//    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);
//    unsigned char * data = new unsigned char[texture_w*texture_h*4];
//    // transfer the bind fbo image data, here is the texture data
//    glReadPixels(0, 0, texture_w, texture_h, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    stbi_write_png("/Users/xxx/Desktop/out.png",texture_w,texture_h,4,data,0);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glDeleteFramebuffers(1, &fbo);

//    // save the texture to image, the second method, just use glGetTexImage()
//    unsigned char * data2 = new unsigned char[texture_w*texture_h*4];
//    glBindTexture(GL_TEXTURE_2D, m_textureID);
//    glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,data2);
//    stbi_write_png("/Users/fordchen/Desktop/out2.png",texture_w,texture_h,4,data2,0);
}

void RenderView::genTextureFromQImage(const QString &path)
{

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    QImage texImage, tempImage;
    bool isLoadOK = tempImage.load(path);
    if(isLoadOK){
        // texImage = QGLWidget::convertToGLFormat(tempImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tempImage.width(), tempImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tempImage.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void RenderView::genTextureFromStbImage(const QString &path)
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels,0);
    if (data)
    {
        texture_w = width;
        texture_h = height;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderView::initRenderThread()
{
    qDebug()<<"GLWidget::initRenderThread() start.";
    auto context = this->context();
    auto mainSurface = context->surface();

    auto renderSurface = new QOffscreenSurface(nullptr,this);
    renderSurface->setFormat(mainSurface->format());
    renderSurface->create();

    context->doneCurrent();
    m_thread = new RenderThread(renderSurface,context,this);
    context->makeCurrent(mainSurface);

    connect(m_thread,&RenderThread::imageReady, this, [this]() { update(); },Qt::QueuedConnection);
    m_thread->setRenderSize(WIDTH,HEIGHT);
    m_thread->start();

    qDebug() << "GLWidget::initRenderThread() end";
}

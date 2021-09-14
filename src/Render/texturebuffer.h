//
// Created by FordChen on 2021/1/11.
//

#ifndef TEXTUREBUFFER_H
#define TEXTUREBUFFER_H

#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QMutex>

#include "Core/Core.h"

CFENGINE_RENDER_START
class TextureBuffer{
public:
    static TextureBuffer *instance();

    /** 未使用
     * 创建一个纹理ID
     * @param context 子线程的context
     */
    void createTexture(QOpenGLContext *context);
    /** 未使用
     * 删除记录的共享纹理ID值
     * @param context 子线程的context
     */
    void deleteTexture(QOpenGLContext *context);
    /** 未使用
     * 拷贝子线程的纹理数据，然后在主线程渲染
     *
     * @param context 子线程的context
     * @param width 共享纹理的宽
     * @param height 共享纹理的高
     */
    void updateTexture(QOpenGLContext *context, int width, int height);
    /**
     * 不拷贝纹理数据，直接使用共享纹理传递ID在主线程进行渲染
     * @param context 子线程的context
     * @param textureID 共享纹理的ID
     */
    void updateTexture(QOpenGLContext *context, int textureID);
    /**
     * 使用共享纹理在主线程进行绘制
     * @param context 主线程的context
     * @param vertexCount 顶点数量
     */
    void drawTexture(QOpenGLContext *context, int vertexCount);

private:
    TextureBuffer();
    ~TextureBuffer();
    TextureBuffer(const TextureBuffer &) = delete;
    TextureBuffer &operator =(const TextureBuffer &) = delete;
    TextureBuffer(const TextureBuffer &&) = delete;
    TextureBuffer &operator =(const TextureBuffer &&) = delete;

    /**
     * 记录共享纹理的ID
     */
    unsigned int m_texture;

    mutable QMutex m_mutex;
};
CFENGINE_RENDER_END
#endif //TEXTUREBUFFER_H

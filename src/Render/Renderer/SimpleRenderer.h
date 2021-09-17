//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_SIMPLERENDERER_H
#define CFRENDERENGINE_SIMPLERENDERER_H

#include "Render/Renderer/Renderer.h"

#include "Core/GL.h"

CFENGINE_RENDER_START

class VertexArray;
class ShaderProgram;
class Texture;

/**
 * 使用shader进行渲染的renderer
 */
class SimpleRenderer: public Renderer , public GL{
public:
    SimpleRenderer();
    SimpleRenderer(const std::string &vertex_shader, const std::string &fragment_shader);

    virtual ~SimpleRenderer();

    bool init() override;

    void render() override;

    void postRender() override;

    void release() override;

    virtual void bindInput();
    virtual void bindOutput();

    void renderInternal();

    /**
     * 设置VAO，即设置VBO顶点数据和IBO索引数据
     * @param vertexArray
     */
    void setVertexArray(std::shared_ptr<VertexArray> vertexArray);

    /**
     * 设置VAO，即设置VBO顶点数据和IBO索引数据
     * @param vertexArray
     */
    void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

    /**
     * 给shader传递纹理数据
     * @param key
     * @param texture 纹理数据
     * @param index
     */
    void setUniformTexture2D(std::string key, std::shared_ptr<Texture> texture, int index);

    /**
   *
   * 设置 uniform vec4 参数
   *
   * @param key 参数名
   * @param value vec4数据，每个vec4是4个float
   * @param count vec4个数
   *
   */
    void setUniformVec4(std::string key, std::vector<float>& value);

    /**
   *
   * 设置 uniform mat4 参数
   *
   * @param key 参数名
   * @param value mat4数据，每个mat4是16个float
   *
   */
    void setUniformMat4(std::string key, std::vector<float>& value);

protected:
    std::shared_ptr<VertexArray> vao_;
    std::shared_ptr<CFEngineRender::ShaderProgram> shader_;

    const std::string DEFAULT_INPUT_TEXTURE_NAME = "u_texture";
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_SIMPLERENDERER_H

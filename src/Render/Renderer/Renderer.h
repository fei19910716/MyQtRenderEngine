//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_RENDERER_H
#define CFRENDERENGINE_RENDERER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Render/Base/FrameBuffer.h"

CFENGINE_RENDER_START
/**
 * 渲染基类，抽象renderer的特征： id, parent_id_, 输入， 输出，具体怎样渲染，用shader渲染还是... 由子类实现
 */
class Renderer: public std::enable_shared_from_this<Renderer> {
public:
    Renderer();
    /**
     * 初始化
     * @return 成功/失败
     */
    virtual bool init() = 0;
    /**
     * 添加一个输入
     * @param frame_buffer 输入 frame buffer
     */
    void setInput(std::shared_ptr<CFEngineRender::FrameBuffer> frame_buffer);
    /**
     * 添加一组输入
     * @param frame_buffers 输入 frame buffers
     */
    void setInput(std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> frame_buffers);
    /**
     * 设置输出
     * @param frame_buffer 输出 frame_buffer
     */
    void setOutput(std::shared_ptr<CFEngineRender::FrameBuffer> frame_buffer);
    /**
     * 获取输出
     * @return 输出 frame buffer
     */
    std::shared_ptr<CFEngineRender::FrameBuffer> output();
    std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>>& input();
    /**
     * 渲染
     */
    virtual void render() = 0;
    /**
     * 设置是否启用，不启用则不渲染
     * 注意，仅当将 renderer 放入 RenderChain/RenderGraph中时此接口生效，如果直接调 renderer 的 Render
     * 接口，不受此接口启动与否控制
     * @param enable 是否启用
     */
    void setEnable(bool enable);
    /**
     * 是否启用，不启用则不渲染
     * 注意，仅当将 renderer 放入 RenderChain/RenderGraph中时此接口生效，如果直接调 renderer 的 Render
     * 接口，不受此接口启动与否控制
     * @return 是否启用
     */
    bool enable();

    virtual void postRender() = 0;
    /**
     * 释放资源
     */
    virtual void release() = 0;

    std::string& id();
    void setId(std::string id);
    std::string& parentId();
    void setParentId(std::string parentId);

protected:
    std::string id_;
    std::string parent_id_;
    bool enable_ = true;

    std::vector<std::shared_ptr<CFEngineRender::FrameBuffer>> input_;
    std::shared_ptr<CFEngineRender::FrameBuffer> output_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_RENDERER_H

//
// Created by fordchen on 2021/9/16.
//

#ifndef CFRENDERENGINE_RENDERGRAPH_H
#define CFRENDERENGINE_RENDERGRAPH_H

#include "GraphNode.h"
#include "Render/Renderer/Renderer.h"

namespace render{
class RenderGraph: public Renderer, public std::enable_shared_from_this<RenderGraph> {
public:
    RenderGraph();
    ~RenderGraph();


    /**
     * 调用所有renderer的init进行初始化
     * @return
     */
    bool init() override;

    void render() override;

    void postRender() override;

    void release() override;

    /**
   *
   * 添加 renderer
   *
   * @param renderer renderer
   * @param id renderer id
   *
   */
    virtual void addRenderer(std::shared_ptr<Renderer> renderer, std::string id);

    /**
     *
     * 添加 renderer
     *
     * @param renderer renderer
     * @param id renderer id
     * @param parent_id  parent renderer id
     *
     * @return this
     *
     */
    virtual void addRenderer(std::shared_ptr<Renderer> renderer, std::string id, std::string parent_id);

    /**
     *
     * 连接 renderer
     *
     * @param preId 前一个 renderer id
     * @param nextId 后一个 renderer id
     *
     * @return this
     *
     */
    virtual void connectRenderer(std::string preId, std::string nextId);

    /**
     *
     * 根据 id 获取 renderer
     *
     * @param id renderer id
     *
     * @return renderer
     *
     */
    std::shared_ptr<Renderer> renderer(std::string id);

protected:
    /**
     * 根据输入节点进行graph的遍历
     * @param start_nodes 输入节点
     */
    void genNodeList();

    void traverseLayer(const std::function<void(std::shared_ptr<render::GraphNode>)>& node_processor);

    std::shared_ptr<render::FrameBuffer> renderByLayer();

protected:
    /**
     * render graph 的输入node，图的输入非唯一
     */
    std::vector<std::shared_ptr<GraphNode>> start_nodes_;
    /**
     * render graph 所有的node
     */
    std::unordered_map<std::string, std::shared_ptr<GraphNode>> renderer_map_;

    /**
     * DFS或者 BFS获得的render graph所有的node列表，依次进行渲染
     */
    std::shared_ptr<std::list<std::shared_ptr<render::GraphNode>>> node_list_;

    bool debug_ = true;

};

}
#endif //CFRENDERENGINE_RENDERGRAPH_H

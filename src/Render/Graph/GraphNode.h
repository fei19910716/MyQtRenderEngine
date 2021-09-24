//
// Created by fordchen on 2021/9/16.
//

#ifndef CFRENDERENGINE_GRAPHNODE_H
#define CFRENDERENGINE_GRAPHNODE_H

#include "Render/Renderer/Renderer.h"
namespace render{

/**
 * 都renderer的封装，用于构建render graph
 */
class GraphNode {
public:
    explicit GraphNode(std::shared_ptr<Renderer> renderer);

    /**
   *
   * 添加下一个node
   *
   * @param next_node 下一个node
   *
   */
    void addNext(std::shared_ptr<GraphNode> next_node);

    /**
   *
   * 添加一个输入
   *
   * @param frame_buffer 输入 frame buffer
   *
   */
    void addInput(std::shared_ptr<render::FrameBuffer> frame_buffer);

    /**
   *
   * 添加一组输入
   *
   * @param frame_buffers 输入 frame buffers
   *
   */
    void addInput(std::vector<std::shared_ptr<render::FrameBuffer>>& frame_buffers);

    std::vector<std::shared_ptr<GraphNode>>& nextNodes();
    std::shared_ptr<Renderer> renderer();
    unsigned int layer();
    void setLayer(unsigned int layer);
    std::vector<std::shared_ptr<render::FrameBuffer>>& input();
    bool enable();
private:
    /**
     * 每个node包含一个renderer
     */
    std::shared_ptr<Renderer> renderer_;
    /**
     * next nodes
     */
    std::vector<std::shared_ptr<GraphNode>> next_nodes_;

    /**
     * node在render graph中的layer
     */
    unsigned int layer_;
};

}
#endif //CFRENDERENGINE_GRAPHNODE_H

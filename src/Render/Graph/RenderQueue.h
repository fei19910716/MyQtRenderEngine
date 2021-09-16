//
// Created by fordchen on 2021/9/16.
//

#ifndef CFRENDERENGINE_RENDERQUEUE_H
#define CFRENDERENGINE_RENDERQUEUE_H

#include "RenderGraph.h"

CFENGINE_RENDER_START
class RenderQueue: public RenderGraph {
public:
    RenderQueue();
    virtual ~RenderQueue();

    void addRenderer(std::shared_ptr<Renderer> renderer, std::string id) override;

    void addRenderer(std::shared_ptr<Renderer> renderer, std::string id, std::string parent_id) override;

    void connectRenderer(std::string preId, std::string curId) override;

protected:
    std::string tail_renderer_id_;
};

CFENGINE_RENDER_END
#endif //CFRENDERENGINE_RENDERQUEUE_H

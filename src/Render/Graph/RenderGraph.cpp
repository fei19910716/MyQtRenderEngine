//
// Created by fordchen on 2021/9/16.
//

#include "RenderGraph.h"

#include "Render/Base/Texture.h"
#include "Render/Base/RenderBuffer.h"
#include "Utils/RenderUtils.h"

#include <queue>
#include <unordered_set>

CFEngineRender::RenderGraph::RenderGraph() {

}

CFEngineRender::RenderGraph::~RenderGraph() {

}

void CFEngineRender::RenderGraph::genNodeList() {
    // 如果不为空，说明遍历过
    if (node_list_ != nullptr) {
        return;
    }
    std::queue<std::shared_ptr<CFEngineRender::GraphNode>> traversalQueue; // 辅助遍历的queue
    std::unordered_set<std::shared_ptr<CFEngineRender::GraphNode>> queuedNodes; // 不重复的node
    std::vector<std::list<std::shared_ptr<CFEngineRender::GraphNode>>> layer_Nodes; // 每一层的node
    // 遍历起始node
    for (auto &startNode : start_nodes_) {
        traversalQueue.push(startNode);
        queuedNodes.insert(startNode);
    }

    while (!traversalQueue.empty()) {
        std::shared_ptr<CFEngineRender::GraphNode> node = traversalQueue.front();
        traversalQueue.pop();
        // 如果是新的layer
        if (node->layer() >= layer_Nodes.size()) {
            layer_Nodes.resize(node->layer() + 1);
        }
        layer_Nodes[node->layer()].push_back(node);
        // BFS遍历，将其子节点加入遍历队列
        for (auto &next : node->nextNodes()) {
            if (queuedNodes.find(next) == queuedNodes.end()) {
                traversalQueue.push(next);
                queuedNodes.insert(next);
            }
        }
    }

    node_list_ = std::make_shared<std::list<std::shared_ptr<CFEngineRender::GraphNode>>>();
    // 根据layer一次加入列表中
    for (auto& layer_ : layer_Nodes) {
        for (auto& node : layer_) {
            node_list_->push_back(node);
        }
    }
}

bool CFEngineRender::RenderGraph::init() {
    bool result = true;
    this->traverseLayer([&](std::shared_ptr<GraphNode> node) {
        result = result && node->renderer()->init();
    });
    return result;
}

void CFEngineRender::RenderGraph::render() {
    output_ = this->renderByLayer();
}

std::shared_ptr<CFEngineRender::FrameBuffer> CFEngineRender::RenderGraph::renderByLayer() {
    if (input_.empty()) {
        return nullptr;
    }
    // 取输出FBO为第一个输入
    std::shared_ptr<CFEngineRender::FrameBuffer> intermediateOutput = input_.front();
    // 如果没有输入节点，则将输入直接作为输出，doNothing
    if (start_nodes_.size() == 0) {
        if (output_ != nullptr && intermediateOutput != output_) {
            // output_->DecreaseRef();
        }
        return intermediateOutput;
    }
    // 初始化第一个节点的inputList
    for (auto& node : start_nodes_) {
        node->addInput(input_);
    }
    for (auto& input : input_) {
        // input->IncreaseRef(start_nodes.size());
    }
    // 开始循环遍历，保证渲染节点和透传节点的inputFB的Ref不变
    traverseLayer([&](std::shared_ptr<CFEngineRender::GraphNode> node) {
        // 节点需要渲染
        if (node->enable()) {
            // TODO 更新当前节点的output，非终结节点从pool里获取FB，终结节点直接使用output_
            if (!node->nextNodes().empty()) {
                auto fbo = std::make_shared<CFEngineRender::FrameBuffer>(400,600);
                node->renderer()->setOutput(fbo);
            } else if (output_ != nullptr) {
                node->renderer()->setOutput(output_);
            }
            // 渲染
            node->renderer()->render();
            intermediateOutput = node->renderer()->output();

            // TODO 把当前节点的inputList都释放一次
            for (auto& node_input : node->input()) {
                if (node_input != intermediateOutput) {
                    // node_input->DecreaseRef();
                }
            }
            // TODO 保存每个render的渲染结果
            if (debug_) {
                Utils::saveFBOToImage( intermediateOutput->handle(),QSize(400,600), "D:\\GameEngine\\CFRenderEngine\\" + node->renderer()->id() + ".png", QOpenGLContext::currentContext());
            }
        } else {  // 节点透传
            intermediateOutput = node->input().front();
            // intermediateOutput->IncreaseRef();
            for (auto& node_input : node->input()) {
                // node_input->DecreaseRef();
            }
        }
        // 更新接下来的节点的inputList，intermediateOutput是当前节点的output，也是接下来的链接的节点的inputList之一
        node->input().clear();
        if (!node->nextNodes().empty()) {
            // intermediateOutput->IncreaseRef(node->nextNodes().size() - 1);
            for (auto& next : node->nextNodes()) {
                next->addInput(intermediateOutput);
            }
        }
    });
    // TODO 内存泄露保护，透传逻辑会导致intermediateOutput不为output_
    if (output_ != nullptr && intermediateOutput != output_) {
        // output_->DecreaseRef();
    }
    // 透传了初始化的输入，对应初始化时IncreaseRef，目前不支持原始多节点输入，size只能为1
    if (intermediateOutput == input_.front()) {
        // intermediateOutput->DecreaseRef();
    }
    return intermediateOutput;
}

void CFEngineRender::RenderGraph::postRender() {

}

void CFEngineRender::RenderGraph::release() {
    this->traverseLayer([](std::shared_ptr<GraphNode> node) {
        node->renderer()->release();
    });
}

void CFEngineRender::RenderGraph::traverseLayer(const std::function<void(std::shared_ptr<CFEngineRender::GraphNode>)>& node_processor) {
    this->genNodeList();

    std::for_each(this->node_list_->begin(), this->node_list_->end(), [&](std::shared_ptr<CFEngineRender::GraphNode> node){
        node_processor(node);
    });
}

void CFEngineRender::RenderGraph::addRenderer(std::shared_ptr<Renderer> renderer, std::string id) {
    if(renderer == nullptr) return;
    renderer->setId(id);

    std::shared_ptr<GraphNode> node = std::make_shared<GraphNode>(renderer);
    renderer_map_[id] = node;
    start_nodes_.push_back(node);
    node_list_ = nullptr; // 需要重新生成
}

void CFEngineRender::RenderGraph::addRenderer(std::shared_ptr<Renderer> renderer, std::string id, std::string parent_id) {
    this->addRenderer(renderer, id);
    renderer->setParentId(parent_id);
}

void CFEngineRender::RenderGraph::connectRenderer(std::string preId, std::string nextId) {
    std::shared_ptr<GraphNode> preNode = renderer_map_[preId];
    std::shared_ptr<GraphNode> nextNode = renderer_map_[nextId];
    preNode->addNext(nextNode);
    auto layer = preNode->layer() + 1 > nextNode->layer() ? preNode->layer() + 1 : nextNode->layer();
    nextNode->setLayer(layer);
    auto iter = std::find(start_nodes_.begin(), start_nodes_.end(), nextNode);
    if (iter != start_nodes_.end()) {
        start_nodes_.erase(iter);
    }
    node_list_ = nullptr;
}

std::shared_ptr<CFEngineRender::Renderer> CFEngineRender::RenderGraph::renderer(std::string id) {
    if (renderer_map_.find(id) != renderer_map_.end()) {
        return renderer_map_[id]->renderer();
    }
    return nullptr;
}

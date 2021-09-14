//
// Created by fordchen on 2021/8/31.
//

#ifndef CFRENDERENGINE_COMPONENTMANAGER_H
#define CFRENDERENGINE_COMPONENTMANAGER_H

#include <QString>
#include <QObject>

#include <unordered_map>

#include "Base/Component.h"

CFENGINE_RENDER_START

class ComponentManager {
public:
    /*
     * 注册需要展示在UI上的组件
     */
    static void registerComponentDescriptions();

    /*
     * 获取所有需要展示在UI上的组件，用于创建添加组件窗口
     */
    static std::unordered_map<ComponentType,std::shared_ptr<ComponentDescription>>& componentDescriptions();

    static std::shared_ptr<ComponentDescription> componentDescriptionWithType(ComponentType type);

public:
    /*
     * 记录所有需要展示在UI上的组件
     */
    static std::unordered_map<ComponentType,std::shared_ptr<ComponentDescription>> allComponentDescriptions_;
};


CFENGINE_RENDER_END
#endif //CFRENDERENGINE_COMPONENTMANAGER_H

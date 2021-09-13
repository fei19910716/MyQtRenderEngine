//
// Created by fordchen on 2021/8/31.
//

#ifndef CFRENDERENGINE_COMPONENTMANAGER_H
#define CFRENDERENGINE_COMPONENTMANAGER_H

#include <QString>
#include <QObject>

#include <unordered_map>

struct ComponentDescription;

class ComponentManager {
public:
    /*
     * 注册需要展示在UI上的组件
     */
    static void registerComponentDescriptions();

    /*
     * 获取所有需要展示在UI上的组件，用于创建添加组件窗口
     */
    static std::vector<ComponentDescription*>& componentDescriptions();

    static ComponentDescription* componentDescriptionWithType(ComponentType type);

public:
    /*
     * 记录所有需要展示在UI上的组件
     */
    static std::unordered_map<ComponentType,ComponentDescription*> allComponentDescriptions_;
};



#endif //CFRENDERENGINE_COMPONENTMANAGER_H

//
// Created by fordchen on 2021/8/31.
//

#ifndef CFRENDERENGINE_COMPONENTMANAGER_H
#define CFRENDERENGINE_COMPONENTMANAGER_H

#include <QString>
#include <QObject>

#include <vector>

#include "Core/entityx.h"

class ComponentDescription;
class Component;

class ComponentManager {
public:
    /*
     * 注册需要展示在UI上的组件
     */
    static void registerComponentDescriptions();

    /*
     * 获取所有需要展示在UI上的组件，用于创建添加组件窗口
     */
    static std::vector<ComponentDescription*> getComponentDescriptions();

    static std::vector<Component*> getComponentsOfEntity(CFEntity& entity);

    template<typename T>
    static bool addComponentOfEntity(CFEntity& entity);

    template<typename T>
    static T* getComponentOfEntity(CFEntity& entity);

    template<typename T>
    static void deleteComponentOfEntity(CFEntity& entity);

public:
    /*
     * 记录所有需要展示在UI上的组件
     */
    static std::vector<ComponentDescription*> allComponentDescriptions_;
};



#endif //CFRENDERENGINE_COMPONENTMANAGER_H

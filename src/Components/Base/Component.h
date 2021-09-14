#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <QString>
#include <QObject>
#include <QVariant>

#include <optional>

#include "Core/Core.h"

CFENGINE_RENDER_START

enum ComponentGroup{
    kPrimitive,
};

enum ComponentPropertyType{
    kString,
    kBool,
    kColor,
    kEnum
};

enum ComponentType{
    kTriangle,
};

struct ComponentPropertyDescription{
    /**
     * 表示组件属性的类型，比如：enum，bool等
     */
    ComponentPropertyType type_;

    std::string name_;
    QString label_;

    /**
     * 属性值是否可编辑
     */
    bool editable_ = true;

    /**
     * 用于想构建slider UI的属性，需要最大值，最小值，步长
     */
    std::optional<float> maxValue_;
    std::optional<float> minValue_;
    std::optional<float> step_;

    /**
     * 默认值
     */
    std::optional<QVariant> defaultValue_;


    std::optional<QStringList> enums_;
};

struct ComponentDescription{
    /**
     * 组件的label，用于在UI上显示
     */
    QString label_;

    /**
     * 组件的类型，用于区分组件，比如：“Triangle"
     */
    ComponentType type_;

    /**
     * 组件的分组
     */
    ComponentGroup group_;

    /**
     * 组件的提示信息
     */
    std::optional<QString> tips_;

    /**
     * 组件是否在inspector面板显示
     */
    std::optional<bool> notDisplayInspectPanel_;

    /**
     * 组件是否可删除
     */
    std::optional<bool> canNotRemove_;

    /**
     * 组件在添加组件窗口中是否隐藏
     */
    std::optional<bool> isHiddenInList_;

    /**
     * 组件是否是全局唯一
     */
    std::optional<bool> isGlobalUnique_;
};

class Component: public QObject{
    Q_OBJECT
    Q_PROPERTY(int componentId READ componentId WRITE setComponentId)
    Q_PROPERTY(int entityId READ entityId WRITE setEntityId)
    Q_PROPERTY(bool enable READ enable WRITE setEnable)
public:
    Component &operator =(const Component &);
    Component() = default;
    Component(int componentId, int entityId);
    Component(const Component& com);

    virtual ~Component();

    int componentId_;
    int entityId_;

public:
    int componentId() const
    {
        return componentId_;
    }
    void setComponentId(int componentId)
    {
        componentId_ = componentId;
    }

    bool enable_ = true;
    bool enable(){
        return enable_;
    }
    void setEnable(bool enable){
        enable_ = enable;
    }


    int entityId() const
    {
        return entityId_;
    }
    void setEntityId(int entityId)
    {
        entityId_ = entityId;
    }

};

CFENGINE_RENDER_END

#endif // COMPONENTS_H

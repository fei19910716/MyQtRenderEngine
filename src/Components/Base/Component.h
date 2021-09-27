#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>
#include <QString>
#include <QObject>
#include <QVariant>

#include <optional>

namespace render{

#define COMPONENT_PROPERTY(Type,fname,name,value) \
Q_PROPERTY(Type name READ name WRITE set##fname)\
Type name() const\
{\
    return name##_;\
}\
void set##fname(Type name)\
{\
    name##_ = name;\
}\
Type name##_ = value;


#define REGISTER_COMPONENT_DESCRIPTION(x) \
auto x##_ptr = std::make_pair(ComponentType::k##x,render::x::MakeComponentDescription());\
allComponentDescriptions_.insert(x##_ptr);

enum ComponentGroup{
    kBase,
    kPrimitive,
};

enum ComponentPropertyType{
    kString,
    kBool,
    kColor,
    kEnum,
    kVec3,
    kFloat
};

enum ComponentType{
    kTriangle,
    kQuad,
    kCube,
    kTransform,
    kCamera,
};

struct ComponentPropertyDescription{
    public:
    ComponentPropertyDescription(std::string name,QString label ):name_(name),label_(label){}
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
public:
    COMPONENT_PROPERTY(int, ComponentId, componentId, 0)
    COMPONENT_PROPERTY(int, EntityId, entityId, 0)
    COMPONENT_PROPERTY(bool, Enable, enable, true)


    Component() = default;
    Component(int componentId, int entityId):componentId_(componentId),entityId_(entityId){}
    Component(const Component& com){
        this->componentId_ = com.componentId();
        this->entityId_ = com.entityId();
    }
    Component &operator =(const Component &com){
        this->componentId_ = com.componentId();
        this->entityId_ = com.entityId();
        return *this;
    }

    virtual ~Component(){}

};

}

#endif // COMPONENTS_H

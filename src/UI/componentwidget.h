#ifndef COMPONENTWIDGET_H
#define COMPONENTWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>

#include "Components/Base/component.h"

class ComponentPropertyDescription;

class ComponentWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * 构造一个component的UI，组件需要展示在UI上的属性需要通过Qt的属性系统声明
     *
     * @param component 当前需要构建UI的组件
     * @param parent 父窗口，一般为null
     */
    explicit ComponentWidget(QWidget *parent = nullptr, Component* component = nullptr);

    /**
     * 构建组件的enum属性的UI
     *
     * @param metaProperty 组件的元属性
     */
    void constructEnum(ComponentPropertyDescription* property);

    /**
     * 构建组件的color属性的UI
     *
     * @param metaProperty 组件的元属性
     */
    void constructColor(ComponentPropertyDescription* property);

    /**
     * 构建组件的bool属性的UI
     *
     * @param metaProperty 组件的元属性
     */
    void constructBool(ComponentPropertyDescription* property);

    /**
     * 构建组件的一般属性的UI，比如：QString
     *
     * @param metaProperty 组件的元属性
     */
    void constructNormal(ComponentPropertyDescription* property);

private:
    QVBoxLayout* mainLayout_;
    Component* component_;

signals:

public slots:
};

#endif // COMPONENTWIDGET_H

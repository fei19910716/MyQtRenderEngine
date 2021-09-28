#pragma once

#include <QWidget>
#include <QObjectUserData>

#include "Components/Base/Component.h"

class QListWidget;

/**
 * 自定义添加Component的窗口，当点击添加组件按钮时在按钮上方弹出该窗口，点击其他区域时关闭窗口
 */
class AddComponentWidget : public QWidget
{
    Q_OBJECT
public:
    struct User : QObjectUserData {
        render::ComponentType type_;
    };

    explicit AddComponentWidget(int width, int height, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *e);
    /**
     * 该窗口的事件处理函数，当点击非该窗口区域时，关闭该窗口，需要处理ActivationChange事件
     * @param event 该窗口的事件
     * @return 事件是否需要传递下去
     */
    bool event(QEvent *event);

signals:
    void componentClicked(QObject* sender);

public slots:


private:
    int width_;
    int height_;
    QListWidget* listWidget_;

};

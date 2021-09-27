#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QDebug>

#include "Entity/Entity.h"

class QListWidgetItem;
class QPushButton;
class AddComponentWidget;
class RenderView;

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * 从一个entity来构建TreeWidgetItem
     *
     * @param ent entity数据
     *
     * @return 构建的QTreeWidgetItem
     */
    QTreeWidgetItem* buildTreeItemFromEntity(render::Entity* entity);

    /**
     * 从一个entity来构建对象树，会递归调用buildTreeItemFromEntity
     *
     * @param root 顶层entity
     *
     * @return 顶层QTreeWidgetItem
     */
    QTreeWidgetItem* buildRootTreeItem(render::Entity* entity);


    /**
     * 创建组件面板
     */
    void constructInspectorPanel();

    /**
     * 创建对象面板的对象树
     */
    void constructEntityPanel();

    /**
     * 对象面板的右键菜单
     */
    void constructEntityTreeMenu();

    /**
     * 设置窗口大小，设置是否全屏，是否最大化显示等
     */
    void initWindowSize();

    void rebuildEntityTree();

    /**
     * 被委托处理其他对象的事件
     * @param obj 委托对象
     * @param event 处理的事件
     * @return 是否处理结束， 如果返回true，则委托对象不需要进行进一步处理
     */
    bool eventFilter(QObject* obj, QEvent* event);

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void onAddComponent(QObject* sender);

    /**
     * 对象面板显示的右键菜单槽函数
     *
     * @param pos 鼠标右键的位置
     */
    void onShowTreeWidgetMenu(QPoint pos);

    void onDisplayComponents(render::Entity* entity);

private:
    Ui::MainWindow *ui;
    /**
     * 对象面板的右键菜单
     */
    QMenu* treeContextMenu_;

    QMenu* treeItemContextMenu_;

    RenderView* renderView_;

    QPushButton* addComponentBtn_;

    AddComponentWidget* addComponentWidget_ = nullptr;
};

#endif // MAINWINDOW_H

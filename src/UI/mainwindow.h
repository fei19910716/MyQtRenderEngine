#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QDebug>

#include "Components/ComponentManager.h"
#include "UI/componentwidget.h"

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MetaInfo;
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
    QTreeWidgetItem* buildTreeItemFromEntity(MetaInfo& metaInfo);

    /**
     * 从一个entity来构建对象树，会递归调用buildTreeItemFromEntity
     *
     * @param root 顶层entity
     *
     * @return 顶层QTreeWidgetItem
     */
    QTreeWidgetItem* buildRootTreeItem(MetaInfo& metaInfo);


    /**
     * 创建组件面板
     */
    void constructInspectorPanel();

    /**
     * 创建对象面板的对象树
     */
    void constructObjectPanel();

    /**
     * 对象面板的右键菜单
     */
    void constructTreeWidgetMenu();

    /**
     * 设置窗口大小，设置是否全屏，是否最大化显示等
     */
    void initWindowSize();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    /**
     * 对象面板显示的右键菜单槽函数
     *
     * @param pos 鼠标右键的位置
     */
    void showTreeWidgetMenuSlot(QPoint pos);

private:
    Ui::MainWindow *ui;
    /**
     * 对象面板的右键菜单
     */
    QMenu* m_contextMenu;
};

#endif // MAINWINDOW_H

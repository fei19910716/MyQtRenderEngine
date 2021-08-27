#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QDebug>

#include "Entities/entity.h"
#include "Components/component.h"
#include "Components/componentwidget.h"

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTreeWidgetItem* buildTreeItemFromEntity(Entity& ent);

    QTreeWidgetItem* buildRootTreeItem(Entity& root);


    QListWidgetItem* buildListItemFromComponent(Component& com);

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

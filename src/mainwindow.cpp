#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>
#include <QScreen>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 获取设备屏幕大小
    // QDesktopWidget* desktopWidget = QApplication::desktop();
    // QRect screenRect = desktopWidget->availableGeometry();
    // QRect screenRect = desktopWidget->screenGeometry();
    auto screenRects = QGuiApplication::screens();
    double screenX = screenRects[0]->size().width();
    double screenY = screenRects[0]->size().height();
    this->setGeometry(0,0,static_cast<int>(screenX),static_cast<int>(screenY));

//    this->showFullScreen();
//    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    this->showMaximized();

    // 设置对象面板
    ui->treeWidget->setColumnCount(1);
    if(QTreeWidgetItem* header = ui->treeWidget->headerItem()) {
      header->setText(0, tr("entities"));
      qDebug() << "header is not null";
    } else {
      ui->treeWidget->setHeaderLabel(tr("entities"));
    }

    ui->treeWidget->setHeaderHidden(true);


    auto root = Entity::getRoot();
    qDebug() << root->id;
    for(auto& item: root->children){
        qDebug() << item.id;
    }
    ui->treeWidget->addTopLevelItem(buildRootTreeItem(*root));


    // 设置组件面板
//    QVBoxLayout *layout = new QVBoxLayout(ui->listWidget);
//    layout->setMargin(10);
//    layout->setSpacing(5);
    for(auto&com : Component::getComponents()){
        const QMetaObject *metaObject = com.metaObject();
        int count = metaObject->propertyCount();
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
          ComponentWidget* cw = new ComponentWidget(this,&com);
        item->setSizeHint(QSize(200,count*40));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,cw);


//        layout->addWidget(cw);
    }
//    layout->addStretch();

//    ui->listWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::buildTreeItemFromEntity(Entity &ent)
{
    QTreeWidgetItem* root = new QTreeWidgetItem();
    root->setText(0,QString::number(ent.id));
    return root;
}

QTreeWidgetItem *MainWindow::buildRootTreeItem(Entity &root)
{
    QTreeWidgetItem* rootItem = buildTreeItemFromEntity(root);
    for(auto& child: root.children){
        auto childItems = buildRootTreeItem(child);
        rootItem->addChild(childItems);
    }
    return rootItem;
}

QListWidgetItem *MainWindow::buildListItemFromComponent(Component &com)
{
    QListWidgetItem* item = new QListWidgetItem();
    //item->setText(com.id);
    return item;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() <<"click : " <<item->text();
}

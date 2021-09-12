#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Components/Base/MetaInfo.h"
#include "Entity/EntityManager.h"
#include "UI/componentwidget.h"

#include "popupwidgetbutton.h"
#include "addcomponentwidget.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initWindowSize();

    this->constructObjectPanel();

    this->constructInspectorPanel();

    // 参考 https://blog.csdn.net/a844651990/article/details/83242159
    PopupWidgetButton *pBtn = new PopupWidgetButton(PWB::Vertical, this, ui->dockWidget_2);
    pBtn->setMinimumSize(150,30);
    QHBoxLayout* addLayout = new QHBoxLayout(ui->dockWidget_2);
    addLayout->addStretch(1);
    addLayout->addWidget(pBtn);
    addLayout->addStretch(1);
    pBtn->button()->setText("Add Component");
    ui->componentPanelLayout->addLayout(addLayout);

    connect(pBtn, &PopupWidgetButton::ButtonClicked,[=](){
        // 弹出窗口
        if(addComponentWidget_ == nullptr){
            addComponentWidget_ = new AddComponentWidget(this);
            pBtn->setMainWidget(addComponentWidget_);
        }
    });

    // ui->dockWidget->setStyleSheet("border: 1px solid black");
    ui->dockWidget->setTitleBarWidget(new QLabel("Entity"));
    ui->dockWidget->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->dockWidget_2->setTitleBarWidget(new QLabel("Component"));
    ui->dockWidget_2->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->dockWidget_4->setTitleBarWidget(new QLabel("Resource"));
    ui->dockWidget_4->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->centralWidget->setStyleSheet("background-color: #f7f2f2; border-bottom: 1px solid black;border-right: 1px solid black;border-left: 1px solid black");

}

void MainWindow::constructInspectorPanel(){
    //! 设置组件面板
    for(auto& com : ComponentManager::getComponents()){
        int count = com->propertyDescriptions_.size();
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        ComponentWidget* cw = new ComponentWidget(this,com);
        item->setSizeHint(QSize(200,count*40));
        ui->listWidget->addItem(item);
        ui->listWidget->setSpacing(2);
        item->setBackgroundColor(QColor(230,230,230));
        ui->listWidget->setItemWidget(item,cw);
    }
}

void MainWindow::constructObjectPanel(){
    //! 设置对象面板
    ui->treeWidget->setColumnCount(1);
    if(QTreeWidgetItem* header = ui->treeWidget->headerItem()) {
        header->setText(0, tr("entities"));
    } else {
        ui->treeWidget->setHeaderLabel(tr("entities"));
    }

    ui->treeWidget->setHeaderHidden(true); // 隐藏header

    this->constructEntityTreeMenu();
}

void MainWindow::initWindowSize(){
//     获取设备屏幕大小
//     QDesktopWidget* desktopWidget = QApplication::desktop();
//     QRect screenRect = desktopWidget->availableGeometry();
//     QRect screenRect = desktopWidget->screenGeometry();
//     auto screenRects = QGuiApplication::screens();
//     double screenX = screenRects[0]->size().width();
//     double screenY = screenRects[0]->size().height();
//     this->setGeometry(0,0,static_cast<int>(screenX)/2,static_cast<int>(screenY)/2);

//     this->showFullScreen(); // 设置全屏显示
//     this->setWindowState(this->windowState() ^ Qt::WindowFullScreen); // 设置全屏显示
//     this->showMaximized(); // 设置最大化显示

    this->resize(1200,800);

    //! 设置glView的size
    ui->openGLWidget->setFixedSize(400,600);
}

void MainWindow::constructEntityTreeMenu(){
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    treeContextMenu_ = new QMenu(ui->treeWidget);
    QAction* m_addAction = new QAction("add Object", this);
    QAction* m_delAction = new QAction("del Object", this);
    treeContextMenu_->addAction(m_addAction);
    treeContextMenu_->addAction(m_delAction);

    treeItemContextMenu_ = new QMenu(ui->treeWidget);
    QAction* m_childAction = new QAction("add Child", this);
    treeItemContextMenu_->addAction(m_childAction);

    connect(m_addAction,&QAction::triggered,[=]{
        EntityManager::createEntity("001","Triangle");
        ui->openGLWidget->m_thread->m_requestRender = true;
        ui->openGLWidget->m_thread->m_condition.wakeOne();
        this->rebuildEntityTree();
    });
    connect(m_delAction,&QAction::triggered,[=]{
        EntityManager::deleteEntity("001");
        this->rebuildEntityTree();
    });
    connect(m_childAction,&QAction::triggered,[=]{
        EntityManager::createEntity("001","GameObejct");

        QTreeWidgetItem* curItem = ui->treeWidget->currentItem();
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0,"GameObejct");
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        curItem->addChild(item);
        curItem->setExpanded(true);
    });
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested,this, &MainWindow::showTreeWidgetMenuSlot);
}

void MainWindow::rebuildEntityTree(){
    auto root = EntityManager::getRoot();
    if(!ENTT::registry.valid(root)) {
        ui->treeWidget->clear();
        return;
    }
    auto metaInfo = ENTT::registry.try_get<MetaInfo>(root);
    ui->treeWidget->addTopLevelItem(this->buildRootTreeItem(*metaInfo));
}

void MainWindow::showTreeWidgetMenuSlot(QPoint pos)
{
    QTreeWidgetItem* curItem = ui->treeWidget->itemAt(pos);  //获取当前被点击的节点
    if (curItem == NULL) 
        treeContextMenu_->exec(QCursor::pos());           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    else
        treeItemContextMenu_->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::buildTreeItemFromEntity(MetaInfo& metaInfo)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,metaInfo.label_);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    return item;
}

QTreeWidgetItem *MainWindow::buildRootTreeItem(MetaInfo& metaInfo)
{
    QTreeWidgetItem* rootItem = buildTreeItemFromEntity(metaInfo);

    for(auto& child: metaInfo.children_){
        auto childItems = buildRootTreeItem(child);
        rootItem->addChild(childItems);
    }
    return rootItem;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() <<"click : " <<item->text();
}

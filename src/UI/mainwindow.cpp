#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Components/Base/MetaInfo.h"
#include "Entity/EntityManager.h"

#include <QDesktopWidget>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initWindowSize();

    this->constructObjectPanel();

    this->constructInspectorPanel();

    connect(ui->openGLWidget, &RenderView::rebuildObejctTree, [=](){
        auto root = EntityManager::getRoot();
        if(!EntityManager::m_registry.valid(root)) {
            ui->treeWidget->clear();
            return nullptr;
        }
        auto metaInfo = EntityManager::m_registry.try_get<MetaInfo>(root);
        ui->treeWidget->addTopLevelItem(this->buildRootTreeItem(*metaInfo));
    });
}

void MainWindow::constructInspectorPanel(){
    //! 设置组件面板
    for(auto& com : ComponentManager::getComponents()){
//        const QMetaObject *metaObject = com->metaObject();
//        int count = metaObject->propertyCount();
        int count = com->propertyDescriptions_.size();
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        ComponentWidget* cw = new ComponentWidget(this,com);
        item->setSizeHint(QSize(200,count*40));
        ui->listWidget->addItem(item);
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

    this->constructTreeWidgetMenu();

    // auto root = EntityManager::getRoot();
    // ui->treeWidget->addTopLevelItem(buildRootTreeItem(root));
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

    //! 设置glView的size
    ui->openGLWidget->setFixedSize(400,600);
}

void MainWindow::constructTreeWidgetMenu(){
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_contextMenu = new QMenu;
    QAction* m_addAction = new QAction("add Object", this);
    QAction* m_delAction = new QAction("del Object", this);
    m_contextMenu->addAction(m_addAction);
    m_contextMenu->addAction(m_delAction);

    connect(m_addAction,&QAction::triggered,ui->openGLWidget,&RenderView::onAddEntity);
    connect(m_delAction,&QAction::triggered,ui->openGLWidget,&RenderView::onDelEntity);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(showTreeWidgetMenuSlot(QPoint)));
}

void MainWindow::showTreeWidgetMenuSlot(QPoint pos)
{
    m_contextMenu->exec(QCursor::pos());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::buildTreeItemFromEntity(MetaInfo& metaInfo)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,metaInfo.label_);
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Components/Base/EntityInfo.h"
#include "Entity/EntityManager.h"
#include "UI/componentwidget.h"
#include "UI/popupwidgetbutton.h"
#include "UI/addcomponentwidget.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initWindowSize();

    this->constructEntityPanel();

    this->constructInspectorPanel();

    // ui->dockWidget->setStyleSheet("border: 1px solid black");
    ui->entityDock->setTitleBarWidget(new QLabel("Entity"));
    ui->entityDock->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->componentDock->setTitleBarWidget(new QLabel("Component"));
    ui->componentDock->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->resourceDock->setTitleBarWidget(new QLabel("Resource"));
    ui->resourceDock->widget()->layout()->setContentsMargins( 0,0,0,0 );

    ui->centralWidget->setStyleSheet("background-color: #f7f2f2; border-bottom: 1px solid black;border-right: 1px solid black;border-left: 1px solid black");
    ui->verticalLayout_2->setAlignment(Qt::AlignHCenter | Qt::AlignHCenter); // 设置renderView居中显示
}

void MainWindow::constructInspectorPanel(){
    // 参考 https://blog.csdn.net/a844651990/article/details/83242159
    PopupWidgetButton *pBtn = new PopupWidgetButton(PWB::Vertical, this, ui->componentDock);
    pBtn->setMinimumSize(150,30);
    QHBoxLayout* addLayout = new QHBoxLayout;
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

            connect(addComponentWidget_,&AddComponentWidget::componentClicked,[=](QObject* sender){
                pBtn->hide();
                this->onAddComponent(sender);
            });
        }
    });
}

void MainWindow::constructEntityPanel(){
    //! 设置对象面板
    ui->entityTreeWidget->setColumnCount(1);
    if(QTreeWidgetItem* header = ui->entityTreeWidget->headerItem()) {
        header->setText(0, tr("entities"));
    } else {
        ui->entityTreeWidget->setHeaderLabel(tr("entities"));
    }

    ui->entityTreeWidget->setHeaderHidden(true); // 隐藏header

    this->constructEntityTreeMenu();

    connect(ui->entityTreeWidget,&QTreeWidget::itemClicked,[=](QTreeWidgetItem *item){
        auto entity = item->data(0,Qt::UserRole).value<CFEntity*>();

        this->onDisplayComponents(entity);

        // render
        ui->renderView->requestRender();
    });
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
    ui->renderView->setFixedSize(400,600);
}

void MainWindow::constructEntityTreeMenu(){
    ui->entityTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    treeContextMenu_ = new QMenu(ui->entityTreeWidget);
    QAction* m_addAction = new QAction("add Object", this);

    treeContextMenu_->addAction(m_addAction);

    treeItemContextMenu_ = new QMenu(ui->entityTreeWidget);
    QAction* m_childAction = new QAction("add Child", this);
    QAction* m_delAction = new QAction("del Object", this);
    treeItemContextMenu_->addAction(m_childAction);
    treeItemContextMenu_->addAction(m_delAction);

    connect(m_addAction,&QAction::triggered,[=]{
        auto entity = EntityManager::createEntity("001","GameObejct");
        QTreeWidgetItem* item = this->buildTreeItemFromEntity(entity);

        QTreeWidgetItem* root = ui->entityTreeWidget->topLevelItem(0);
        if(root == nullptr){
            ui->entityTreeWidget->addTopLevelItem(item);
            root = item;
        }
        root->addChild(item);
        root->setExpanded(true);
        item->setSelected(true);
        ui->entityTreeWidget->setCurrentItem(item);
        auto ent = item->data(0,Qt::UserRole).value<CFEntity*>();
        this->onDisplayComponents(ent);
        // render
        ui->renderView->requestRender();
    });
    connect(m_delAction,&QAction::triggered,[=]{
        QTreeWidgetItem* curItem = ui->entityTreeWidget->currentItem();
        auto entity = curItem->data(0,Qt::UserRole).value<CFEntity*>();
        EntityManager::deleteEntity(entity);

        if(curItem->parent() == nullptr){
            ui->entityTreeWidget->clear();
            ui->componentListWidget->clear();
        }else{
            auto parent = curItem->parent();
            parent->removeChild(curItem);
            parent->setSelected(true);
            ui->entityTreeWidget->setCurrentItem(parent);
            auto entity = parent->data(0,Qt::UserRole).value<CFEntity*>();
            this->onDisplayComponents(entity);
        }


        // render
        ui->renderView->requestRender();
    });
    connect(m_childAction,&QAction::triggered,[=]{
        auto entity = EntityManager::createEntity("001","GameObejct");

        QTreeWidgetItem* curItem = ui->entityTreeWidget->currentItem();
        QTreeWidgetItem* item = this->buildTreeItemFromEntity(entity);
        curItem->addChild(item);
        curItem->setExpanded(true);
        item->setSelected(true);
        ui->entityTreeWidget->setCurrentItem(item);
        auto ent = item->data(0,Qt::UserRole).value<CFEntity*>();
        this->onDisplayComponents(ent);

        // render
        ui->renderView->requestRender();
    });
    connect(ui->entityTreeWidget, &QTreeWidget::customContextMenuRequested,this, &MainWindow::onShowTreeWidgetMenu);
}

void MainWindow::rebuildEntityTree(){
    auto root = EntityManager::root();
    if(!root->valid()) {
        ui->entityTreeWidget->clear();
        return;
    }
    ui->entityTreeWidget->clear();
    ui->entityTreeWidget->addTopLevelItem(this->buildRootTreeItem(root));
}

void MainWindow::onShowTreeWidgetMenu(QPoint pos)
{
    QTreeWidgetItem* curItem = ui->entityTreeWidget->itemAt(pos);  //获取当前被点击的节点
    if (curItem == NULL) 
        treeContextMenu_->exec(QCursor::pos());           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    else
        treeItemContextMenu_->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem *MainWindow::buildTreeItemFromEntity(CFEntity* entity)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();

    auto metaInfo = entity->component<CFEngineRender::EntityInfo>();
    item->setData(0,Qt::UserRole,QVariant::fromValue<CFEntity*>(entity));
    item->setText(0,metaInfo->label_);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    return item;
}

QTreeWidgetItem *MainWindow::buildRootTreeItem(CFEntity* entity)
{
    QTreeWidgetItem* rootItem = buildTreeItemFromEntity(entity);

    for(auto& child: entity->children_){
        auto childItems = buildRootTreeItem(child);
        rootItem->addChild(childItems);
    }
    return rootItem;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() <<"click : " <<item->text();
}

void MainWindow::onAddComponent(QObject* sender) {


    QTreeWidgetItem* curItem = ui->entityTreeWidget->currentItem();
    auto entity = curItem->data(0,Qt::UserRole).value<CFEntity*>();

    QPushButton *pButton = qobject_cast<QPushButton *>(sender);

    // 获取第一个用户数据
    AddComponentWidget::User *pUser = (AddComponentWidget::User *)(pButton->userData(Qt::UserRole+1));

    switch(pUser->type_){
        case CFEngineRender::ComponentType::kTriangle:
            entity->addComponent<CFEngineRender::Triangle>();
            break;
    }
    this->onDisplayComponents(entity);
    // render
    ui->renderView->requestRender();
}

void MainWindow::onDisplayComponents(CFEntity* entity){
    //! 设置组件面板
    if(!entity->valid())
        return;
    ui->componentListWidget->clear();
    for(auto& com : entity->allComponents()){
        if(com == nullptr)
            continue;
        auto uiCom = dynamic_cast<CFEngineRender::UIComponent*>(com);
        if(uiCom == nullptr)
            continue;
        int count = uiCom->propertyDescriptions_.size();
        if(count == 0)
            continue;
        QListWidgetItem* item = new QListWidgetItem(ui->componentListWidget);
        ComponentWidget* cw = new ComponentWidget(this,uiCom);
        item->setSizeHint(QSize(200,count*40));
        ui->componentListWidget->addItem(item);
        ui->componentListWidget->setSpacing(2);
        item->setBackgroundColor(QColor(230,230,230));
        ui->componentListWidget->setItemWidget(item,cw);

        connect(cw, &ComponentWidget::componentChanged,[=](CFEngineRender::Component* component){
            QTreeWidgetItem* curItem = ui->entityTreeWidget->currentItem();
            auto entity = curItem->data(0,Qt::UserRole).value<CFEntity*>();
            
            this->onDisplayComponents(entity);
            ui->renderView->requestRender();
        });
    }
}

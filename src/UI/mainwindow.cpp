#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Components/Base/EntityInfo.h"
#include "Entity/EntityManager.h"
#include "UI/componentwidget.h"
#include "UI/AddComponentWidget.h"

#include <QDesktopWidget>
#include <QWidgetAction>
#include <QScreen>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <Components/Primitive/Quad.h>
#include "Components/Primitive/Triangle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initWindowSize();

    this->constructEntityPanel();

    this->constructInspectorPanel();

    QLabel* entity = new QLabel("Entity",this);
    entity->setAlignment(Qt::AlignCenter);
    ui->entityDock->setTitleBarWidget(entity);
    ui->entityDock->widget()->layout()->setContentsMargins( 2,2,2,0);

    QLabel* component = new QLabel("Component",this);
    component->setAlignment(Qt::AlignCenter);
    ui->componentDock->setTitleBarWidget(component);
    ui->componentDock->widget()->layout()->setContentsMargins( 2,2,2,0);

    QLabel* resource = new QLabel("Resource",this);
    resource->setAlignment(Qt::AlignCenter);
    ui->resourceDock->setTitleBarWidget(resource);
    ui->resourceTreeWidget->setHeaderHidden(true); // 隐藏header
    ui->resourceDock->widget()->layout()->setContentsMargins( 2,2,2,0);

    ui->centralWidget->setStyleSheet("background-color: #f7f2f2; border-bottom: 1px solid black;border-right: 1px solid black;border-left: 1px solid black");
    ui->verticalLayout_2->setAlignment(Qt::AlignHCenter | Qt::AlignHCenter); // 设置renderView居中显示




    QMenu *file_menu = new QMenu("文件(&F)",ui->menuBar);
    QMenu *edit_menu = new QMenu("编辑(&E)",ui->menuBar);
    QMenu *help_menu = new QMenu("帮助(&H)",ui->menuBar);

    //创建动作
    QAction *new_action = new QAction("新建(&N)");
    QAction *open_action = new QAction("打开(&O)");
    QAction *save_action = new QAction("保存(&S)");

    //添加状态栏提示
    new_action->setStatusTip("新建一个文件或项目");
    open_action->setStatusTip("打开一个文件或项目");
    save_action->setStatusTip("保存");

    //添加动作到新建菜单，QAction就会自动变成子菜单
    file_menu->addAction(new_action);
    file_menu->addAction(open_action);
    file_menu->addSeparator();                      //添加菜单分隔符
    file_menu->addAction(save_action);

    //给编辑菜单添加子菜单
    edit_menu->addAction("剪切(&T)");
    //给帮助菜单添加子菜单
    help_menu->addAction("关于(&A)");

    //把菜单添加到菜单栏
    ui->menuBar->addMenu(file_menu);
    ui->menuBar->addMenu(edit_menu);
    ui->menuBar->addMenu(help_menu);


    setWindowTitle("render engine");
}

void MainWindow::constructInspectorPanel(){

    addComponentBtn_ = new QPushButton(this);
    addComponentBtn_->setMinimumSize(150,30);
    QHBoxLayout* addLayout = new QHBoxLayout;
    addLayout->addStretch(1);
    addLayout->addWidget(addComponentBtn_);
    addLayout->addStretch(1);
    addComponentBtn_->setText("Add Component");
    ui->componentPanelLayout->addLayout(addLayout);

    { //!点击按钮弹出菜单窗口
//        addComponentMenu_ = new QMenu(this);
//        auto size = addComponentBtn_->size();
//        QLabel* text = new QLabel( "Triangle" );
//        text->setStyleSheet("background-color: gray");
//        text->setAlignment( Qt::AlignVCenter | Qt::AlignHCenter );
//        text->setFixedSize(size.width()*1.5, size.height()*1.3);
//        QWidgetAction* triangle = new QWidgetAction( addComponentMenu_ );
//        triangle->setDefaultWidget(text);
//        addComponentMenu_->addAction(triangle);
//
//        addComponentBtn_->setMenu(addComponentMenu_);
//        addComponentMenu_->installEventFilter(this); // 将addComponentMenu_的事件委托给this先处理
//
//        connect(triangle, &QWidgetAction::triggered,[=](){
//            // 弹出窗口
//            this->onAddComponent(triangle);
//        });
    }



    addComponentBtn_->setStyleSheet(
            //正常状态样式
            "QPushButton{"
            "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
            "border-style:outset;"                  //边框样式（inset/outset）
            "border-width:2px;"                     //边框宽度像素
            "border-radius:10px;"                   //边框圆角半径像素
            "border-color:rgba(255,255,255,30);"    //边框颜色
            "font-size: 10px;"                       //字体，字体大小
            "color:rgba(0,0,0,200);"                //字体颜色
            "padding:6px;"                          //填衬
            "}"
            //鼠标按下样式
            "QPushButton:pressed{"
            "background-color:rgba(100,255,100,200);"
            "border-color:rgba(255,255,255,30);"
            "border-style:inset;"
            "color:rgba(0,0,0,100);"
            "}"
            //鼠标悬停样式
            "QPushButton:hover{"
            "background-color:rgba(100,255,100,100);"
            "border-color:rgba(255,255,255,200);"
            "color:rgba(0,0,0,200);"
            "}"
            "QPushButton::menu-indicator{image:none}");

    addComponentWidget_ = new AddComponentWidget();
    addComponentWidget_->installEventFilter(this);
    addComponentWidget_->setFixedSize(addComponentBtn_->width()*1.5, addComponentBtn_->height()*5);

    connect(addComponentBtn_,&QPushButton::clicked,[=](){
        addComponentWidget_->show(); // show调用时，会收到QEvent::Show事件，然后由this先处理
    });

    connect(addComponentWidget_,&AddComponentWidget::componentClicked,[=](QObject* sender){
        this->onAddComponent(sender);
    });

}

bool MainWindow::eventFilter(QObject* obj, QEvent* event){
    if(event->type() == QEvent::Show && obj == addComponentWidget_){
        int width = addComponentWidget_->width();
        int height = addComponentWidget_->height();
        int buttonWidth = addComponentBtn_->width();
        int buttonX = addComponentBtn_->mapToGlobal(QPoint(0,0)).x();
        int buttonY = addComponentBtn_->mapToGlobal(QPoint(0,0)).y();

        QPoint pos = QPoint(buttonX + (buttonWidth - width) / 2, buttonY - height);

        addComponentWidget_->move(pos);
        return true;
    }
    return false;
}

void MainWindow::constructEntityPanel(){
    //! 设置对象面板
    ui->entityTreeWidget->setColumnCount(1);
    if(QTreeWidgetItem* header = ui->entityTreeWidget->headerItem()) {
        header->setText(0, tr("entities"));
    } else {
        ui->entityTreeWidget->setHeaderLabel(tr("entities"));
    }
    // ui->entityTreeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
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

    if(curItem == nullptr)
        return;
    auto entity = curItem->data(0,Qt::UserRole).value<CFEntity*>();

    QPushButton *btn = qobject_cast<QPushButton*>(sender);

    AddComponentWidget::User* pUser = (AddComponentWidget::User *)btn->userData(Qt::UserRole+1);
    EntityManager::addComponentWithType(entity,pUser->type_);

    this->onDisplayComponents(entity);
    // render
    ui->renderView->requestRender();
}

void MainWindow::onDisplayComponents(CFEntity* entity){
    //! 设置组件面板
    if(!entity->valid())
        return;
    ui->componentListWidget->clear();
    for(auto& com : EntityManager::allComponents(entity)){
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

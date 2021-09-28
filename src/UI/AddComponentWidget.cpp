#include "addcomponentwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QListWidget>
#include <QApplication>

#include "Components/ComponentManager.h"
#include "UI/ComponentHeaderWidget.h"
AddComponentWidget::AddComponentWidget(int width, int height, QWidget *parent):QWidget(parent), width_(width), height_(height)

{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    listWidget_ = new QListWidget;
    listWidget_->setSpacing(2);
    listWidget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    listWidget_->verticalScrollBar()->setFixedWidth(10);
    listWidget_->setFixedSize(width_,height_);

    QVBoxLayout* main_layout= new QVBoxLayout;
    main_layout->setMargin(0);
    main_layout->addWidget(listWidget_);

    this->setLayout(main_layout);

    // 获取所有的分组
    std::unordered_map<render::ComponentGroup,std::vector<std::shared_ptr<render::ComponentDescription>>> group;
    for(auto& item: render::ComponentManager::componentDescriptions()){
        auto componentDescription = item.second;

        if(group.find(componentDescription->group_) == group.end()){
            group.insert(std::make_pair<render::ComponentGroup,std::vector<std::shared_ptr<render::ComponentDescription>>>(
                    static_cast<render::ComponentGroup &&>(componentDescription->group_), {}) );
        }
        auto ite = group.find(componentDescription->group_);
        ite->second.push_back(componentDescription);
    }

    // 生成每个group的UI
    for(auto& pair: group){
        // 生成header widget
        ComponentHeaderWidget* m_headerButton = new ComponentHeaderWidget;
        m_headerButton->setObjectName("ComponentHeaderWidget");
        m_headerButton->SetTextLabel(render::ComponentGroupToString.find(pair.first)->second);
        //m_sizeButton->SetImageLabel(QPixmap(":/Dialog/Resources/Collapse.png"));
        m_headerButton->setStyleSheet("background-color:rgba(34,50,42,0.5)");

        QLabel* sizeLabel = m_headerButton->GetTextHandle();
        sizeLabel->setStyleSheet("QLabel{color:rgba(183,71,42,1)}");
        sizeLabel->setFont(QFont("", 10, QFont::Black));

        // 每个contentWidget 的布局
        QVBoxLayout *contentLayout = new QVBoxLayout(this);
        contentLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        contentLayout->setMargin(0);
        contentLayout->setSpacing(2);

        QWidget* m_contentWidget = new QWidget;
        m_contentWidget->setParent(this);
        m_contentWidget->setVisible(true);

        QWidget* itemWidget = new QWidget;
        QListWidgetItem* item = new QListWidgetItem;
        auto componentDescriptions = pair.second;
        int count = componentDescriptions.size();
        for(auto& componentDescription: componentDescriptions){
            QPushButton* com = new QPushButton(this);
            com->setFixedWidth(120);
            com->setText(componentDescription->label_);
            User *user = new User;
            user->type_ = componentDescription->type_;
            com->setUserData(Qt::UserRole+1, user);
            com->setStyleSheet(
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

            connect(com, &QPushButton::clicked,[=](){
                this->close();
                emit componentClicked(com);
            });
            contentLayout->addWidget(com);
        }
        connect(m_headerButton, &ComponentHeaderWidget::clicked, [=](bool) {
            if (m_headerButton->collapse()) {
                m_headerButton->SetImageLabel(QPixmap(":/Dialog/Resources/Expand.png"));
                m_contentWidget->setVisible(true);
                m_contentWidget->setFixedSize(QSize(width_,(count+1)*30));
                item->setSizeHint(QSize(width_,(count+1)*30));
                m_headerButton->setCollapse(false);
            } else {
                m_headerButton->SetImageLabel(QPixmap(":/Dialog/Resources/Collapse.png"));
                //m_sizeList偶数屏蔽Size列表界面，奇数显示Size列表界面
                m_contentWidget->setVisible(false);
                m_contentWidget->setFixedSize(QSize(width_,30));
                item->setSizeHint(QSize(width_,30));
                m_headerButton->setCollapse(true);
            }
        });
        m_contentWidget->setLayout(contentLayout);


        QVBoxLayout* itemWidgetLayout = new QVBoxLayout;
        itemWidgetLayout->setAlignment(Qt::AlignTop);
        itemWidgetLayout->setMargin(0);
        itemWidgetLayout->addWidget(m_headerButton);
        itemWidgetLayout->addWidget(m_contentWidget);

        itemWidget->setLayout(itemWidgetLayout);
        listWidget_->addItem(item);

        item->setBackgroundColor(QColor(230,230,230));
        listWidget_->setItemWidget(item,itemWidget);

        m_headerButton->setCollapse(true);
        m_contentWidget->setVisible(false);
    }


}

bool AddComponentWidget::event(QEvent *event) {
    if (event->type() == QEvent::ActivationChange)
    {
        if(QApplication::activeWindow() != this)
        {
            this->close();
        }
    }
    return QWidget::event(event); // 事件传递给父类处理
}

void AddComponentWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

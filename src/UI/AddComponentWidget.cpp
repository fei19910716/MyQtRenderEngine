#include "addcomponentwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QApplication>

#include "Components/ComponentManager.h"
#include <QGraphicsDropShadowEffect>
AddComponentWidget::AddComponentWidget(QWidget *parent)
    : QFrame(parent)
{
    QHBoxLayout *pMainLayout = new QHBoxLayout(this);
    pMainLayout->setAlignment(Qt::AlignTop);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    for(auto& item: CFEngineRender::ComponentManager::componentDescriptions()){
        QPushButton* com = new QPushButton(this);
        com->setText(item.second->label_);
        User *user = new User;
        user->type_ = item.second->type_;
        com->setUserData(Qt::UserRole+1, user);
        com->setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:2px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:bold 10px;"                       //字体，字体大小
                "color:rgba(0,0,0,100);"                //字体颜色
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
        pMainLayout->addWidget(com);
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

#include "ComponentHeaderWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QMenu>

ComponentHeaderWidget::ComponentHeaderWidget(QWidget* parent): QWidget(parent), collapse_(false)
{
    m_imageBtn = new QPushButton;
    m_imageBtn->setFixedWidth(20);
    // m_imageBtn->setScaledContents(true);
    m_imageBtn->setStyleSheet("QLabel{background-color:transparent;}");

    m_textLabel = new QLabel;
    m_textLabel->setStyleSheet("QLabel{background-color:transparent;}");

    m_settingBtn = new QPushButton;
    m_settingBtn->setFixedWidth(30);
    m_settingBtn->setText("*");
    QMenu* menu = new QMenu();
    QAction* delAction = new QAction("del");
    menu->addAction(delAction);
    m_settingBtn->setMenu(menu);
    m_settingBtn->setStyleSheet("QPushButton::menu-indicator{ image:none;width:0px;}");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_imageBtn);
    mainLayout->addWidget(m_textLabel);
    mainLayout->addWidget(m_settingBtn);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);

    connect(m_imageBtn, &QPushButton::clicked,[=](bool value){ clicked(value);});
    connect(delAction,  &QAction::triggered,  [=]{ removeComponent();});
}

void ComponentHeaderWidget::SetImageLabel(const QPixmap &pixmap)
{
    m_imageBtn->setIcon(pixmap);
}

void ComponentHeaderWidget::SetTextLabel(QString text)
{
    m_textLabel->setText(text);
}

QPushButton* ComponentHeaderWidget::GetImageHandle()
{
    return m_imageBtn;
}

QLabel* ComponentHeaderWidget::GetTextHandle()
{
    return m_textLabel;
}

bool ComponentHeaderWidget::collapse() {
    return collapse_;
}

void ComponentHeaderWidget::setCollapse(bool collapse) {
    collapse_ = collapse;
}





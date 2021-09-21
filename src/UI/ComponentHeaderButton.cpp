#include "ComponentHeaderButton.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>

ComponentHeaderButton::ComponentHeaderButton(QWidget* parent): QPushButton(parent), collapse_(false)
{
    m_imageLabel = new QLabel;
    m_imageLabel->setFixedWidth(20);
    m_imageLabel->setScaledContents(true);
    m_imageLabel->setStyleSheet("QLabel{background-color:transparent;}");

    m_textLabel = new QLabel;
    m_textLabel->setStyleSheet("QLabel{background-color:transparent;}");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_imageLabel);
    mainLayout->addWidget(m_textLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);
}

void ComponentHeaderButton::SetImageLabel(const QPixmap &pixmap)
{
    m_imageLabel->setPixmap(pixmap);
}

void ComponentHeaderButton::SetTextLabel(QString text)
{
    m_textLabel->setText(text);
}

QLabel* ComponentHeaderButton::GetImageHandle()
{
    return m_imageLabel;
}

QLabel* ComponentHeaderButton::GetTextHandle()
{
    return m_textLabel;
}

bool ComponentHeaderButton::collapse() {
    return collapse_;
}

void ComponentHeaderButton::setCollapse(bool collapse) {
    collapse_ = collapse;
}





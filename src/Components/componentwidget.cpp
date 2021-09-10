#include "componentwidget.h"

#include <QMetaProperty>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>
#include <QColorDialog>
#include <QPushButton>
#include <QCheckBox>

ComponentWidget::ComponentWidget(QWidget *parent, Component* component) : QWidget(parent), component_(component)
{
    // 设置布局
    mainLayout_ = new QVBoxLayout;

    // 遍历组件所有需要展示的属性
    for(auto& property: component_->propertyDescriptions_){
        switch (property->type_) {
            case ComponentPropertyType::kBool:
                constructBool(property);
                break;
            case ComponentPropertyType::kColor:
                constructColor(property);
                break;
            case ComponentPropertyType::kEnum:
                constructEnum(property);
                break;
            default:
                constructNormal(property);
                break;
        }
    }
    this->setLayout(mainLayout_);
}

void ComponentWidget::constructBool(ComponentPropertyDescription* property){

    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    auto propertyName = property->name_.c_str();
    QVariant value = component_->property(propertyName);
    QCheckBox* checkBox = new QCheckBox;
    checkBox->setChecked(value.toBool());
    checkBox->setEnabled(property->editable_);

    connect(checkBox,&QCheckBox::stateChanged,[&](int state){
        qDebug() << "enable------------" << propertyName;
        qDebug() << "state------------" << (state == Qt::Checked);
        component_->setProperty(propertyName,(state == Qt::Checked));
        qDebug() << "state------------" << component_->property(propertyName).toBool();
    });

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(checkBox);
    mainLayout_->addLayout(hLayout);
}

void ComponentWidget::constructNormal(ComponentPropertyDescription* property){
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());
    QLineEdit* uiValue = new QLineEdit;
    uiValue->setText(value.toString());
    uiValue->setEnabled(property->editable_);

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(uiValue);
    mainLayout_->addLayout(hLayout);
}

void ComponentWidget::constructColor(ComponentPropertyDescription* property){
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());
    QPushButton* btn = new QPushButton;
    // 设置button的背景色
    auto setButtonColor = [=](QColor color){
        QPalette pal = btn->palette();
        pal.setColor(QPalette::ButtonText, Qt::white);
        pal.setColor(QPalette::Button, color);
        btn->setAutoFillBackground(true);
        btn->setPalette(pal);
        btn->setFlat(true);
    };
    setButtonColor(value.value<QColor>());

    connect(btn,&QPushButton::clicked,[=](){
        QColor color=QColorDialog::getColor();
        if(color.isValid())
        {
            setButtonColor(color);
        }

        // btn->setStyleSheet("background-color: rgb(170, 0, 255);");
    });

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(btn);
    hLayout->addStretch(1);
    mainLayout_->addLayout(hLayout);
}

void ComponentWidget::constructEnum(ComponentPropertyDescription* property){
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());

    QComboBox* comBox = new QComboBox;
    comBox->clear();
    comBox->addItems(property->enums_.value());
    comBox->setCurrentIndex(value.toInt());

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(comBox);
    mainLayout_->addLayout(hLayout);
}

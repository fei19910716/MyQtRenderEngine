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
#include <QListWidgetItem>

#include "ComponentHeaderButton.h"

ComponentWidget::ComponentWidget(QListWidgetItem* item, render::UIComponent* component, QWidget *parent)
    : QWidget(parent),
      component_(component),
      item_(item)
{

    ComponentHeaderButton* m_headerButton = new ComponentHeaderButton;
    m_headerButton->setObjectName("ComponentHeaderButton");
    m_headerButton->SetTextLabel(component_->componentDescription()->label_);
    //m_sizeButton->SetImageLabel(QPixmap(":/Dialog/Resources/Collapse.png"));
    m_headerButton->setStyleSheet("#ComponentHeaderButton{background-color:transparent}"
                                  "#ComponentHeaderButton:hover{background-color:rgba(195,195,195,0.4)}"
                                  "#ComponentHeaderButton:pressed{background-color:rgba(127,127,127,0.4)}");

    QWidget* m_contentWidget = new QWidget;
    m_contentWidget->setParent(this);
    m_contentWidget->setVisible(true);

    QLabel* sizeLabel = m_headerButton->GetTextHandle();
    sizeLabel->setStyleSheet("QLabel{color:rgba(183,71,42,1)}");
    sizeLabel->setFont(QFont("", 10, QFont::Black));


    // 设置布局
    mainLayout_ = new QVBoxLayout;
    int count = component_->propertyDescriptions_.size();
    // 遍历组件所有需要展示的属性
    for(auto& property: component_->propertyDescriptions_){
        switch (property->type_) {
            case render::ComponentPropertyType::kBool:
                constructBool(property);
                break;
            case render::ComponentPropertyType::kColor:
                constructColor(property);
                break;
            case render::ComponentPropertyType::kEnum:
                constructEnum(property);
                break;
            default:
                constructNormal(property);
                break;
        }
    }
    m_contentWidget->setLayout(mainLayout_);

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->setAlignment(Qt::AlignTop);
    vlayout->setMargin(0);
    vlayout->addWidget(m_headerButton);
    vlayout->addWidget(m_contentWidget);

    this->setLayout(vlayout);

    connect(m_headerButton, &ComponentHeaderButton::clicked, [=](bool) {
        if (m_headerButton->collapse()) {
            m_headerButton->SetImageLabel(QPixmap(":/Dialog/Resources/Expand.png"));
            m_contentWidget->setVisible(true);
            item->setSizeHint(QSize(200,(count+1)*30));
            m_headerButton->setCollapse(false);
        } else {
            m_headerButton->SetImageLabel(QPixmap(":/Dialog/Resources/Collapse.png"));
            //m_sizeList偶数屏蔽Size列表界面，奇数显示Size列表界面
            m_contentWidget->setVisible(false);
            item->setSizeHint(QSize(200,30));
            m_headerButton->setCollapse(true);
        }
    });

}

void ComponentWidget::constructBool(std::shared_ptr<render::ComponentPropertyDescription> property){

    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    auto propertyName = property->name_.c_str();
    QVariant value = component_->property(propertyName);
    QCheckBox* checkBox = new QCheckBox;
    checkBox->setChecked(value.toBool());
    checkBox->setEnabled(property->editable_);

    connect(checkBox,&QCheckBox::stateChanged,[=](int state){
        component_->setProperty(propertyName,(state == Qt::Checked));
        emit componentChanged(component_);
    });

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(checkBox);
    mainLayout_->addLayout(hLayout);
}

void ComponentWidget::constructNormal(std::shared_ptr<render::ComponentPropertyDescription> property){
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

void ComponentWidget::constructColor(std::shared_ptr<render::ComponentPropertyDescription> property){
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());
    QPushButton* btn = new QPushButton;
    btn->setFixedWidth(80);
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

void ComponentWidget::constructEnum(std::shared_ptr<render::ComponentPropertyDescription> property){
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

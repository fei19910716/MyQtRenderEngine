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
#include <QDoubleSpinBox>
#include <QListWidgetItem>

#include "ComponentHeaderWidget.h"
#include "Core/glm.h"

Q_DECLARE_METATYPE(glm::vec3)

ComponentWidget::ComponentWidget(QListWidgetItem* item, render::UIComponent* component, QWidget *parent)
    : QWidget(parent),
      component_(component),
      item_(item)
{

    ComponentHeaderWidget* m_headerButton = new ComponentHeaderWidget;
    m_headerButton->setObjectName("ComponentHeaderWidget");
    m_headerButton->SetTextLabel(component_->componentDescription()->label_);
    //m_sizeButton->SetImageLabel(QPixmap(":/Dialog/Resources/Collapse.png"));
    m_headerButton->setStyleSheet("background-color:rgba(34,50,42,0.5)");

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
            case render::ComponentPropertyType::kVec3:
                constructVec3(property);
                break;
            case render::ComponentPropertyType::kFloat:
                constructFloat(property);
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

    connect(m_headerButton, &ComponentHeaderWidget::clicked, [=](bool) {
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

    connect(m_headerButton, &ComponentHeaderWidget::removeComponent, [=](){ componentRemoved(item_,component_);});

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

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(uiName);
    hLayout->addWidget(checkBox);
    mainLayout_->addLayout(hLayout);

    connect(checkBox,&QCheckBox::stateChanged,[=](int state){
        component_->setProperty(propertyName,(state == Qt::Checked));
        emit componentChanged(component_);
    });
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

void ComponentWidget::constructVec3(std::shared_ptr<render::ComponentPropertyDescription> property){
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());
    glm::vec3 vec3 = value.value<glm::vec3>();

    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* label_x = new QLabel("x");
    QDoubleSpinBox* line_x = new QDoubleSpinBox;
    line_x->setFixedWidth(60);
    line_x->setSingleStep(0.1);
    line_x->setValue(vec3.x);
    QLabel* label_y = new QLabel("y");
    QDoubleSpinBox* line_y = new QDoubleSpinBox;
    line_y->setValue(vec3.y);
    line_y->setSingleStep(0.1);
    line_y->setFixedWidth(60);
    QLabel* label_z = new QLabel("z");
    QDoubleSpinBox* line_z = new QDoubleSpinBox;
    line_z->setValue(vec3.z);
    line_z->setSingleStep(0.1);
    line_z->setFixedWidth(60);

    layout->addWidget(uiName);
    layout->addWidget(label_x);
    layout->addWidget(line_x);
    layout->addWidget(label_y);
    layout->addWidget(line_y);
    layout->addWidget(label_z);
    layout->addWidget(line_z);


    mainLayout_->addLayout(layout);

    auto fun = [=](double value){
        auto propertyName = property->name_.c_str();
        component_->setProperty(propertyName,QVariant::fromValue(glm::vec3(line_x->value(),line_y->value(),line_z->value())));
        emit componentChanged(component_);
    };

    connect(line_x,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),fun);
    connect(line_y,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),fun);
    connect(line_z,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),fun);

}

void ComponentWidget::constructFloat(std::shared_ptr<render::ComponentPropertyDescription> property) {
    QLabel* uiName = new QLabel(property->label_);
    uiName->setFixedWidth(80);

    // 拿到component存储的值
    QVariant value = component_->property(property->name_.c_str());

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignLeft);
    QDoubleSpinBox* spinBox = new QDoubleSpinBox;
    spinBox->setSingleStep(0.1);
    spinBox->setValue(value.toFloat());

    layout->addWidget(uiName);
    layout->addWidget(spinBox);

    mainLayout_->addLayout(layout);

    auto fun = [=](double value){
        auto propertyName = property->name_.c_str();
        component_->setProperty(propertyName,spinBox->value());
        emit componentChanged(component_);
    };

    connect(spinBox,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),fun);
}

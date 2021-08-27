#include "componentwidget.h"

#include <QMetaProperty>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

ComponentWidget::ComponentWidget(QWidget *parent, Component* component) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    const QMetaObject *metaObject = component->metaObject();
    int count = metaObject->propertyCount();
    for (int i = 0 ; i< count; ++i) {
        QMetaProperty metaProperty = metaObject->property(i);
        const char *name = metaProperty.name();

        QVariant value = component->property(name);

        QLabel* uiName = new QLabel(tr(name));
        qDebug() << "name: " << uiName->text();

        QLineEdit* uiValue = new QLineEdit;
        uiValue->setText(value.toString());
        qDebug() << "value: " << uiValue->text();
        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->addWidget(uiName);
        hLayout->addWidget(uiValue);
        mainLayout->addLayout(hLayout);
    }
    this->setLayout(mainLayout);
}

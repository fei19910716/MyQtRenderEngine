#ifndef COMPONENTWIDGET_H
#define COMPONENTWIDGET_H

#include <QWidget>
#include <QDebug>

#include "component.h"

class ComponentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentWidget(QWidget *parent = nullptr, Component* component = nullptr);

signals:

public slots:
};

#endif // COMPONENTWIDGET_H

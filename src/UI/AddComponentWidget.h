#pragma once

#include <QWidget>
#include <QObjectUserData>

#include "Components/Base/cfcomponent.h"

class AddComponentWidget : public QWidget
{
    Q_OBJECT
public:
    struct User : QObjectUserData {
        ComponentType type_;
    };

    explicit AddComponentWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *e);

signals:
    void componentClicked(QObject* sender);

public slots:

};

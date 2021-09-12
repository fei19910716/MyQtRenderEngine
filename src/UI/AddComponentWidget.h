#pragma once

#include <QWidget>

class AddComponentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddComponentWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *e);

signals:

public slots:

};

#pragma once

#include <QWidget>
#include <QDebug>

class AddComponentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddComponentWidget(QWidget *parent = nullptr):QWidget(parent){
        setWindowFlags((Qt::Dialog | Qt::FramelessWindowHint | this->windowFlags()));
        //setAttribute(Qt::WA_TranslucentBackground);
        setMouseTracking(true);
    }
};
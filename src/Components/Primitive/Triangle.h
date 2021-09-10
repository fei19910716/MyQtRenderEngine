#pragma once

#include <QColor>

#include <vector>

#include "Components/component.h"

class Triangle: public Component{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(bool enable READ enable WRITE setEnable)
    Q_PROPERTY(QColor color READ color)
    Q_PROPERTY(Priority priority READ priority)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    Triangle(){}
    Triangle(int componentId, int entityId):Component(componentId,entityId){
        ComponentPropertyDescription* name = new ComponentPropertyDescription;
        name->name_ = "name";
        name->label_ = "name";
        name->type_ = ComponentPropertyType::kString;
        name->editable_ = false;

        ComponentPropertyDescription* priority = new ComponentPropertyDescription;
        priority->name_ = "priority";
        priority->label_ = "priority";
        priority->type_ = ComponentPropertyType::kEnum;
        priority->enums_ = {"High","Low","VeryHigh","VeryLow"};

        ComponentPropertyDescription* color = new ComponentPropertyDescription;
        color->name_ = "color";
        color->label_ = "color";
        color->type_ = ComponentPropertyType::kColor;

        ComponentPropertyDescription* enable = new ComponentPropertyDescription;
        enable->name_ = "enable";
        enable->label_ = "enable";
        enable->type_ = ComponentPropertyType::kBool;

        this->propertyDescriptions_.emplace_back(name);
        this->propertyDescriptions_.emplace_back(priority);
        this->propertyDescriptions_.emplace_back(color);
        this->propertyDescriptions_.emplace_back(enable);
    }


    std::vector<float> vertices = {
            -0.5f, 0.5f, 0.0f, // left
            0.5f, 0.5f, 0.0f, // right
            0.0f,  0.0f, 0.0f  // top
    };

    std::vector<unsigned int> indices = {
            0, 1, 2,  // first Triangle
    };

public:

    bool enable_ = true;
    bool enable(){
        return enable_;
    }
    void setEnable(bool enable){
        enable_ = enable;
    }

    QString name_ = "Triangle";
    QString name(){
        return name_;
    }


    QColor color_ = QColor(255, 0, 0, 127);
    QColor color(){
        return color_;
    }

    Priority priority_ = Priority::Low;
    Priority priority(){
        return priority_;
    }

signals:
};

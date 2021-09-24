#pragma once

#include <QWidget>
#include <QPushButton>

class QLabel;

class ComponentHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    /// @brief 构造方法
    explicit ComponentHeaderWidget(QWidget* parent = nullptr);

    /// @brief SetImageLabel
    /// 设置按钮图标
    void SetImageLabel(const QPixmap &pixmap);

    /// @brief SetTextLabel
    /// 设置按钮文字
    void SetTextLabel(QString text);

    /// @brief GetImageHandle
    /// 返回m_imageLabel
    QPushButton* GetImageHandle();

    /// @brief GetImageHandle
    /// 返回m_textLabel
    QLabel* GetTextHandle();

    bool collapse();

    void setCollapse(bool collapse);

signals:
    void clicked(bool);
    void removeComponent();

private:
    // 按钮图标
    QPushButton* m_imageBtn;
    // 按钮文字
    QLabel* m_textLabel;
    // 设置按钮
    QPushButton* m_settingBtn;

    bool collapse_;
};



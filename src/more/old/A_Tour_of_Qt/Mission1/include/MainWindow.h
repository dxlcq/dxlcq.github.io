#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     centralWidget;
    QVBoxLayout vLayout;        // 垂直布局

    QLineEdit   input, output;  // 输入框，输出框
    QGridLayout gLayout;        // 网格布局
    QPushButton btn[4][4];      // 按钮

    void btnNumClicked();       // 数字点击事件
    void btnOpClicked();        // 操作符点击事件
    void btnClearClicked();     // 清除点击事件
    void btnDelClicked();       // 删除点击事件
};
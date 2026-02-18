#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT                  

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private:
    QWidget     _centralWidget;
    QHBoxLayout _hLayout;       // 水平布局
    QLineEdit   _input, _output;// 文本框
    QPushButton _button;        // 按钮

    void _onButtonClicked();    // 按钮点击的槽函数
};
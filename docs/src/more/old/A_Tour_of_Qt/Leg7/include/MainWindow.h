#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中心窗口
    QHBoxLayout _layout;        // 水平布局
    QComboBox   _comboBox;      // 下拉框
    QPushButton _button;        // 按钮
    QMessageBox _messageBox;    // 消息框
};
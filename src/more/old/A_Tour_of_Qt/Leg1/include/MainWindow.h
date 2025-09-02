#pragma once

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow   // 创建一个主窗口类
{                                       // 继承自QMainWindow
    Q_OBJECT                            // 使用Qt的信号与槽机制需要这个宏

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private:
    // 在这里声明私有成员变量和私有方法
    QLabel *_label;                     // 声明一个文本标签
};
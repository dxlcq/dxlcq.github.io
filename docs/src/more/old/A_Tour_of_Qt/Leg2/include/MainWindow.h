// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget     *_centralWidget;// 声明一个中央部件
    QVBoxLayout *_vLayout;      // 声明一个垂直布局管理器
    QGridLayout *_gLayout;      // 声明一个网格布局管理器
    // 创建 6 个文本标签
    QLabel      _labeltext_1,
                _labeltext_2,
                _labeltext_3,
                _labeltext_4,
                _labeltext_5,
                _labeltext_6;
    QLabel      *_labelimg;     // 声明一个图片标签
};
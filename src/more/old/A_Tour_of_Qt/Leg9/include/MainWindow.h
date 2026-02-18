#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget; // 中心窗口
    QHBoxLayout     _layout;        // 水平布局
    QSlider         _slider;        // 滑动条
    QLabel          _label;         // 标签
};
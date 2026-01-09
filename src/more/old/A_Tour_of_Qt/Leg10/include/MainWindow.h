#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    bool ck(int x, int y);          // 检查是否越界
    QWidget         _centralWidget; // 中心窗口
    QPushButton     _button_up,
                    _button_down,
                    _button_left,
                    _button_right;  // 按钮 上下左右
    QSlider         _slider;        // 滑动条
    QLabel          _label;         // 图片
};
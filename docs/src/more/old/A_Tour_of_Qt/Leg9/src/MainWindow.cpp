#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg9 滑动条");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    
    _layout.addWidget(&_slider);        // 将滑动条添加到布局中
    _layout.addWidget(&_label);         // 将标签添加到布局中

    _slider.setRange(0, 99);   // 设置滑动条的范围
    _slider.setOrientation(Qt::Horizontal); // 设置滑动条的方向
    _slider.setValue(49);       // 设置滑动条的当前值

    _label.setText("50");       // 设置标签的文本

    // 连接信号和槽
    connect(&_slider, &QSlider::valueChanged, this, [=](int value){
        _label.setText(QString::number(value)); // 将滑动条的值转换为字符串并设置为标签的文本
    });
}

MainWindow::~MainWindow(){}
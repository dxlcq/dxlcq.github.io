#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg8 进度条");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_progressBar);           // 将进度条添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    // 设置进度条的范围
    _progressBar.setRange(0, 100);
    // 设置进度条的当前值
    _progressBar.setValue(0);

    // 设置按钮的文本
    _button.setText("点击增加进度条的值");

    // 通过空格键来控制进度条的增长
    connect(&_button, &QPushButton::clicked, &_progressBar, [&](){
        if(_progressBar.value() == 100)
            QMessageBox::information(this, "提示", "进度条已经满了");
        _progressBar.setValue(_progressBar.value() + 1);
    });
}

MainWindow::~MainWindow(){}
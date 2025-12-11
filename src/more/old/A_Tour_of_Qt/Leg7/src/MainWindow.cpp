#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 7 下拉列表");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_comboBox);              // 将下拉框添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    _comboBox.addItem("鱼香肉丝");               // 添加下拉框的选项
    _comboBox.addItem("宫保鸡丁");
    _comboBox.addItem("糖醋排骨");

    _button.setText("确定");                    // 设置按钮的文本

    connect(&_button, &QPushButton::clicked, this, [this](){
        QMessageBox::information(nullptr, "提示", "你选择了：" + _comboBox.currentText());
    });
}

MainWindow::~MainWindow(){}
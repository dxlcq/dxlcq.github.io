#include "../include/MainWindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Mission2 模糊搜索");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_comboBox);              // 将下拉框添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    // 读取文件
    std::ifstream ifs("data.txt");
    std::string line;
    while (std::getline(ifs, line))
        _comboBox.addItem(QString::fromStdString(line));

    // 设置下拉框可编辑
    _comboBox.setEditable(true);
    // 设置下拉框的模糊搜索
    _comboBox.setCompleter(new QCompleter(_comboBox.model()));


    // 设置按钮的文本
    _button.setText("确定");
    
    // 设置按钮的点击事件
    connect(&_button, &QPushButton::clicked, this, [this](){
        QMessageBox::information(nullptr, "提示", "你选择了：" + _comboBox.currentText());
    });
}

MainWindow::~MainWindow(){}
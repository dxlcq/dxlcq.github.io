#include "include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Leg 3 按钮与文本框");
    
    setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_hLayout);// 设置中心窗口的布局

    _hLayout.addWidget(&_input);    // 将文本框添加到布局中
    _hLayout.addWidget(&_button);   // 将按钮添加到布局中
    _hLayout.addWidget(&_output);   // 将文本框添加到布局中

    _button.setText("转换");        // 设置按钮的文本
    _output.setReadOnly(true);      // 设置输出文本框为只读

    // 连接按钮的点击信号与槽函数
    connect(&_button, &QPushButton::clicked, this, &MainWindow::_onButtonClicked);
}

void MainWindow::_onButtonClicked(){
    QString input = _input.text();  // 获取输入文本框的内容
    if (input.isEmpty()){           // 检测输入是否为空
        QMessageBox::warning(this, "警告", "输入不能为空");
        return;                     // 如果为空，弹出警告框
    }

    for (auto &c : input){          // 检测输入是否是小写字母
        if (c < 'a' || c > 'z'){    // 如果不是小写字母，弹出警告框
            QMessageBox::warning(this, "警告", "输入必须是小写字母");
            return;
        }
    }

    QString output = input.toUpper();   // 将输入转换为大写
    _output.setText(output);            // 将转换后的内容设置到输出文本框中
}

MainWindow::~MainWindow(){}
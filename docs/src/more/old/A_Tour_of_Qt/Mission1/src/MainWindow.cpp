#include "include/MainWindow.h"
#include "include/calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("四则计算器");

    setCentralWidget(&centralWidget);
    centralWidget.setLayout(&vLayout);

    vLayout.addWidget(&input);
    vLayout.addWidget(&output);
    vLayout.addLayout(&gLayout);

    // 设置输入输出框只读
    input.setReadOnly(true);
    output.setReadOnly(true);

    // 将按钮添加到布局中
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            gLayout.addWidget(&btn[i][j], i, j);
        }
    
    // 设置按钮文本
    btn[0][0].setText("7");
    btn[0][1].setText("8");
    btn[0][2].setText("9");
    btn[0][3].setText("+");
    btn[1][0].setText("4");
    btn[1][1].setText("5");
    btn[1][2].setText("6");
    btn[1][3].setText("-");
    btn[2][0].setText("1");
    btn[2][1].setText("2");
    btn[2][2].setText("3");
    btn[2][3].setText("*");
    btn[3][0].setText("C");
    btn[3][1].setText("0");
    btn[3][2].setText("D");
    btn[3][3].setText("/");

    // 设置数字按钮的点击事件
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            connect(&btn[i][j], &QPushButton::clicked, this, &MainWindow::btnNumClicked);
        }
    connect(&btn[3][1], &QPushButton::clicked, this, &MainWindow::btnNumClicked);

    // 设置操作符按钮的点击事件
    for(int i = 0; i < 4; i++)
        connect(&btn[i][3], &QPushButton::clicked, this, &MainWindow::btnOpClicked);
    
    // 设置清除按钮的点击事件
    connect(&btn[3][0], &QPushButton::clicked, this, &MainWindow::btnClearClicked);
    // 设置删除按钮的点击事件
    connect(&btn[3][2], &QPushButton::clicked, this, &MainWindow::btnDelClicked);
}

void MainWindow::btnNumClicked(){
    QPushButton* btn = (QPushButton*)sender();
    QString str = btn -> text();
    input.setText(input.text() + str);

    // 计算结果
    output.setText( QString::fromStdString( infix( input.text().toStdString() ) ) );
}

void MainWindow::btnOpClicked(){
    QPushButton* btn = (QPushButton*)sender();
    QString str = btn -> text();

    if( !(input.text().back() >= '0' && input.text().back() <= '9') )
        return; // 如果最后一个字符不是数字，直接返回
    
    input.setText(input.text() + str);

    output.setText( QString::fromStdString( infix( input.text().toStdString() ) ) );
}

void MainWindow::btnClearClicked(){
    input.clear();
    output.clear();

    output.setText( QString::fromStdString( infix( input.text().toStdString() ) ) );
}

void MainWindow::btnDelClicked(){
    QString str = input.text();
    str.chop(1);
    input.setText(str);

    output.setText( QString::fromStdString( infix( input.text().toStdString() ) ) );
}

MainWindow::~MainWindow(){}
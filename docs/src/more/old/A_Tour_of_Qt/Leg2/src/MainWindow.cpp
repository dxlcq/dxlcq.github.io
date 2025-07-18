// MainWindow.cpp
#include "include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Leg 2 布局管理器");

    _centralWidget  = new QWidget();
    _vLayout        = new QVBoxLayout();
    _gLayout        = new QGridLayout();
    _labelimg       = new QLabel();

    setCentralWidget(_centralWidget);       // 设置中央部件
    _centralWidget -> setLayout(_vLayout);  // 设置中央部件的布局管理器

    _vLayout -> addLayout(_gLayout);        // 将网格布局管理器添加到垂直布局管理器
    _vLayout -> addWidget(_labelimg);       // 将图片标签添加到垂直布局管理器

    // 将 6 个文本标签添加到网格布局管理器，并且设置内容
    _gLayout -> addWidget(&_labeltext_1, 0, 0);
    _gLayout -> addWidget(&_labeltext_2, 0, 1);
    _gLayout -> addWidget(&_labeltext_3, 0, 2);
    _gLayout -> addWidget(&_labeltext_4, 1, 0);
    _gLayout -> addWidget(&_labeltext_5, 1, 1);
    _gLayout -> addWidget(&_labeltext_6, 1, 2);
    _labeltext_1.setText("C"); _labeltext_1.setAlignment(Qt::AlignCenter);
    _labeltext_2.setText("Q"); _labeltext_2.setAlignment(Qt::AlignCenter);
    _labeltext_3.setText("V"); _labeltext_3.setAlignment(Qt::AlignCenter);
    _labeltext_4.setText("I"); _labeltext_4.setAlignment(Qt::AlignCenter);
    _labeltext_5.setText("E"); _labeltext_5.setAlignment(Qt::AlignCenter);
    _labeltext_6.setText("!"); _labeltext_6.setAlignment(Qt::AlignCenter);

    // 设置图片标签，并且设置为居中
    _labelimg  -> setPixmap(QPixmap("img/cqvie.jpg"));
    _labelimg  -> setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete _labelimg;
    delete _gLayout;
    delete _vLayout;
    delete _centralWidget;
}
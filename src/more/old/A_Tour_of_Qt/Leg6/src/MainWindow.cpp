#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 6 列表");
    _centralWidget  = new QWidget();
    _layout         = new QHBoxLayout();
    _listWidget     = new QListWidget();
    _lineEdit       = new QLineEdit();

    setCentralWidget(_centralWidget);
    _centralWidget -> setLayout(_layout);
    _layout -> addWidget(_listWidget);
    _layout -> addWidget(_lineEdit);

    _lineEdit -> setReadOnly(true);

    _listWidget -> addItem("鱼香肉丝");
    _listWidget -> addItem("宫保鸡丁");
    _listWidget -> addItem("糖醋排骨");

    connect(_listWidget, &QListWidget::itemClicked, this, &MainWindow::_onSelect);
}

MainWindow::~MainWindow(){
    delete _centralWidget;
    delete _layout;
    delete _listWidget;
    delete _lineEdit;
}

void MainWindow::_onSelect(QListWidgetItem* item){
    _lineEdit -> setText(item -> text());
}
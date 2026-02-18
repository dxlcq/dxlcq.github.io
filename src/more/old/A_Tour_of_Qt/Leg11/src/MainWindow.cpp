#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 11 滑动窗口");
    this -> setCentralWidget(&_centralWidget);
    _centralWidget.setLayout(&_layout);

    _layout.addWidget(&_listWidget);    // 左侧列表窗口
    _layout.addWidget(&_stackedWidget); // 右侧堆叠窗口

    _listWidget.addItem("窗口 1");
    _listWidget.addItem("窗口 2");
    _listWidget.addItem("窗口 3");

    _stackedWidget.addWidget(&_scrollArea1); // 右侧第一个窗口
    _stackedWidget.addWidget(&_scrollArea2); // 右侧第二个窗口
    _stackedWidget.addWidget(&_scrollArea3); // 右侧第三个窗口

    _contextWidget1.setLayout(&_layout1); // 右侧第一个窗口的布局
    _contextWidget2.setLayout(&_layout2); // 右侧第二个窗口的布局
    _contextWidget3.setLayout(&_layout3); // 右侧第三个窗口的布局

    connect(&_listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);
}

MainWindow::~MainWindow(){}

void MainWindow::onItemClicked(QListWidgetItem *item){
    if(item -> text() == "窗口 1"){
        _stackedWidget.setCurrentWidget(&_scrollArea1);
        // 直接给窗口怼一个标签
        QLabel *label = new QLabel(QString("第 1 个窗口，第 %1 次点击").arg(++cnt1), &_contextWidget1);
        _scrollArea1.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout1.addWidget(label);
        _scrollArea1.setWidget(&_contextWidget1);
        // 定位到最后
        QScrollBar *vScrollBar = _scrollArea1.verticalScrollBar();
        vScrollBar->setValue(vScrollBar->maximum());
    }
    else if(item -> text() == "窗口 2"){
        _stackedWidget.setCurrentWidget(&_scrollArea2);
        QLabel *label = new QLabel(QString("第 2 个窗口，第 %1 次点击").arg(++cnt2)); 
        _scrollArea2.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout2.addWidget(label);
        _scrollArea2.setWidget(&_contextWidget2);
    }
    else if(item -> text() == "窗口 3"){
        _stackedWidget.setCurrentWidget(&_scrollArea3);
        QLabel *label = new QLabel(QString("第 3 个窗口，第 %1 次点击").arg(++cnt3));
        _scrollArea3.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout3.addWidget(label);
        _scrollArea3.setWidget(&_contextWidget3);
    }
}
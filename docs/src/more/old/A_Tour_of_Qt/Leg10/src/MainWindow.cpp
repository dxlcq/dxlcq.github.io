#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("leg10 设置大小");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整

    // 设置按钮
    _button_up.setParent   (&_centralWidget);
    _button_down.setParent (&_centralWidget);
    _button_left.setParent (&_centralWidget);
    _button_right.setParent(&_centralWidget);

    _button_up.setText   ("up");    
    _button_down.setText ("down");  
    _button_left.setText ("left");  
    _button_right.setText("right"); 

    _button_up.setGeometry   (100, 0, 100, 100);
    _button_down.setGeometry (100, 100, 100, 100);
    _button_left.setGeometry (0,   100, 100, 100);
    _button_right.setGeometry(200, 100, 100, 100);

    // 设置滑动条
    _slider.setParent(&_centralWidget);
    _slider.setOrientation(Qt::Horizontal);
    _slider.setRange(100, 300);
    _slider.setValue(200);
    _slider.setGeometry(0, 200, 300, 100);

    // 设置图片
    _label.setParent(&_centralWidget);
    
    QPixmap pixmap("Leg10.png");    // 读取图片 保持长宽比例缩放 图片平滑处理
    pixmap = pixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _label.setPixmap(pixmap);
    _label.setGeometry(0, 300, 200, 200);

    connect(&_button_up, &QPushButton::clicked, [&](){
        if(!ck(_label.x(), _label.y() - 10)) return;
        _label.move(_label.x(), _label.y() - 10);
    });

    connect(&_button_down, &QPushButton::clicked, [&](){
        if(!ck(_label.x(), _label.y() + 10)) return;
        _label.move(_label.x(), _label.y() + 10);
    });
    connect(&_button_left, &QPushButton::clicked, [&](){
        if(!ck(_label.x() - 10, _label.y())) return;
        _label.move(_label.x() - 10, _label.y());
    });
    connect(&_button_right, &QPushButton::clicked, [&](){
        if(!ck(_label.x() + 10, _label.y())) return;
        _label.move(_label.x() + 10, _label.y());
    });

    connect(&_slider, &QSlider::valueChanged, [&](int value){
        QPixmap pixmap("Leg10.png");    // 读取图片 保持长宽比例缩放 图片平滑处理
        pixmap = pixmap.scaled(QSize(value, value), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        _label.setPixmap(pixmap);
        _label.setGeometry(_label.x(), _label.y(), value, value);
    });
}

bool MainWindow::ck(int x, int y){
    if(x < 0 || x > 1080 || y < 0 || y > 720) return false;
    if(x < 300 && y < 300) return false;
    return true;
}

MainWindow::~MainWindow(){}
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 14 定时器");
    this -> setCentralWidget(&_centralWidget);
    this -> resize(400, 300);

    _labeltext.setParent(&_centralWidget);
    _labeltext.setText("Hello World!");

    _timer.start(5);

    int lastDx = 10, lastDy = 10;
    connect(&_timer, &QTimer::timeout, this, [&](){
        int x = _labeltext.x(), y = _labeltext.y();
        int nx = x + lastDx, ny = y + lastDy;

        if(nx >=1 && nx <= 320 && ny >= 1 && ny <= 280 && x != nx && y != ny)
            _labeltext.move(nx, ny);
        else{
            lastDx = QRandomGenerator::global()->bounded(10)-5;
            lastDy = QRandomGenerator::global()->bounded(10)-5;
        }
    });
}

MainWindow::~MainWindow(){}
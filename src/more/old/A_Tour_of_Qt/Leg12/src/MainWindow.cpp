#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 11 Qt绘图");
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口

    _A.setParent(&_centralWidget);
    _B.setParent(&_centralWidget);
    _lineEdit_A_X.setParent(&_centralWidget);
    _lineEdit_A_Y.setParent(&_centralWidget);
    _lineEdit_B_X.setParent(&_centralWidget);
    _lineEdit_B_Y.setParent(&_centralWidget);

    _A.setText("A点坐标");
    _B.setText("B点坐标");
    _lineEdit_A_X.setText("123");
    _lineEdit_A_Y.setText("123");
    _lineEdit_B_X.setText("456");
    _lineEdit_B_Y.setText("456");

    _A.setGeometry(0, 0, 50, 50);
    _B.setGeometry(100, 0, 50, 50);
    _lineEdit_A_X.setGeometry(50, 0, 50, 25);
    _lineEdit_A_Y.setGeometry(50, 25, 50, 25);
    _lineEdit_B_X.setGeometry(150, 0, 50, 25);
    _lineEdit_B_Y.setGeometry(150, 25, 50, 25);

}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);
    int A_X = _lineEdit_A_X.text().toInt(),
        A_Y = _lineEdit_A_Y.text().toInt(),
        B_X = _lineEdit_B_X.text().toInt(),
        B_Y = _lineEdit_B_Y.text().toInt();
    painter.drawLine(QPoint(A_X, A_Y), QPoint(B_X, B_Y));
}

MainWindow::~MainWindow(){}
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("鼠标检测器");
    this -> setCentralWidget(&_centralWidget);
    this -> setFixedSize(800, 600);

    _x_y.setParent(&_centralWidget);
    _x_y.setGeometry(0, 0, 100, 20);
    _x_y.setText("x: 0, y: 0");

    setMouseTracking(true); // 鼠标跟踪
}

MainWindow::~MainWindow(){}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    // 鼠标外形
    painter.drawRect(300, 200, 200, 300);   // 坐标 长宽
    
    // 鼠标左键
    if(_l_pressed) painter.setBrush(Qt::red);
    painter.drawRect(300, 200, 90, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标右键
    if(_r_pressed) painter.setBrush(Qt::red);
    painter.drawRect(410, 200, 90, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标中键
    if(_m_pressed) painter.setBrush(Qt::red);
    painter.drawRect(390, 200, 20, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标前进
    if(_wheel_up) painter.setPen(QPen(Qt::red, 6));
    else painter.setPen(QPen(Qt::black, 6));
    painter.drawLine(400, 100, 400, 175);
    painter.drawLine(400, 95, 375, 125);
    painter.drawLine(400, 95, 425, 125);
    _wheel_up = 0;

    // 鼠标后退
    if(_wheel_down) painter.setPen(QPen(Qt::red, 6));
    else painter.setPen(QPen(Qt::black, 6));
    painter.drawLine(400, 400, 400, 475);
    painter.drawLine(375, 450, 400, 480);
    painter.drawLine(425, 450, 400, 480);
    _wheel_down = 0;
    
} // 真的服了，这个坐标太反人类了

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event -> button() == Qt::LeftButton)
        _l_pressed = 1; // 鼠标左键
    if(event -> button() == Qt::RightButton)
        _r_pressed = 1; // 鼠标右键
    if(event -> button() == Qt::MiddleButton)
        _m_pressed = 1; // 鼠标中键
    update();           // 重绘
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event -> button() == Qt::LeftButton)
        _l_pressed = 0; // 鼠标左键
    if(event -> button() == Qt::RightButton)
        _r_pressed = 0; // 鼠标右键
    if(event -> button() == Qt::MiddleButton)
        _m_pressed = 0; // 鼠标中键
    update();           // 重绘
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    _x_y.setText(QString("x: %1, y: %2").arg(event -> pos().x()).arg(event -> pos().y()));
    update();
}

void MainWindow::wheelEvent(QWheelEvent *event){
    if(event ->angleDelta().y() == 0) _wheel_up = 0, _wheel_down = 0;
    else if(event ->angleDelta().y() > 0) _wheel_up = 1, _wheel_down = 0;
    else if(event ->angleDelta().y() < 0) _wheel_down = 1, _wheel_up = 0;
    update();

    // 233ms 后执行一次
    QTimer::singleShot(233, this, [=](){
        _wheel_up = 0, _wheel_down = 0;
        update();
    });
}
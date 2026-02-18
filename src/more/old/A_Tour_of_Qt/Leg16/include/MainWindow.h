#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget;

    void paintEvent(QPaintEvent *event);

    bool _l_pressed=0, _r_pressed=0, _m_pressed=0;
    // 鼠标按下
    void mousePressEvent(QMouseEvent *event);
    // 鼠标释放
    void mouseReleaseEvent(QMouseEvent *event);

    // 鼠标移动
    QLabel      _x_y;
    void mouseMoveEvent(QMouseEvent *event);

    // 鼠标滚轮
    bool _wheel_up=0, _wheel_down=0;
    void wheelEvent(QWheelEvent *event);
};
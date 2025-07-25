#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QPainter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中心窗口
    QMenuBar    _menuBar;       // 菜单栏

    QLabel      _label;         // 状态标签

    QMenu       _shape;         // 形状菜单
        QAction     _line;      // 直线
        QAction     _rectangle; // 矩形
        QAction     _ellipse;   // 椭圆
        QAction     _polygon;   // 多边形
    QString     _shape_str;     // 当前选择的形状
    
    QMenu       _color_A;       // 外部线条颜色
        QAction     _A_black;   // 黑色
        QAction     _A_red;     // 红色
        QAction     _A_green;   // 绿色
        QAction     _A_blue;    // 蓝色
    QString     _color_A_str;   // 当前选择的外部线条颜色
    
    QMenu       _color_B;       // 内部填充颜色
        QAction     _B_black;   // 黑色
        QAction     _B_red;     // 红色
        QAction     _B_green;   // 绿色
        QAction     _B_blue;    // 蓝色
    QString     _color_B_str;   // 当前选择的内部填充颜色
    
    QAction     _width;         // 线条宽度
    QString     _width_str;     // 当前选择的线条宽度

    void paintEvent(QPaintEvent *event);
};
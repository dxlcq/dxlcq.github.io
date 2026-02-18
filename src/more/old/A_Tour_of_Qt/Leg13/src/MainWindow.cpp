#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 12 绘制多种图形");
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    this -> setMenuBar(&_menuBar);              // 设置菜单栏

    _menuBar.addMenu(&_shape);  // 添加 形状 菜单
    _shape.setTitle("形状");
        _line.setText("直线");      _shape.addAction(&_line);
        _rectangle.setText("矩形"); _shape.addAction(&_rectangle);
        _ellipse.setText("椭圆");   _shape.addAction(&_ellipse);
        _polygon.setText("多边形"); _shape.addAction(&_polygon);
    _shape_str = "直线";
    
    _menuBar.addMenu(&_color_A);// 添加 外部线条颜色 菜单
    _color_A.setTitle("外部线条颜色");
        _A_black.setText("black");   _color_A.addAction(&_A_black);
        _A_red.setText("red");     _color_A.addAction(&_A_red);
        _A_green.setText("green");   _color_A.addAction(&_A_green);
        _A_blue.setText("blue");    _color_A.addAction(&_A_blue);
    _color_A_str = "black";

    _menuBar.addMenu(&_color_B);// 添加 内部填充颜色 菜单
    _color_B.setTitle("内部填充颜色");
        _B_black.setText("black");   _color_B.addAction(&_B_black);
        _B_red.setText("red");     _color_B.addAction(&_B_red);
        _B_green.setText("green");   _color_B.addAction(&_B_green);
        _B_blue.setText("blue");    _color_B.addAction(&_B_blue);
    _color_B_str = "black";
    
    _menuBar.addAction(&_width);// 添加 线条宽度 菜单
    _width.setText("线条宽度");
    _width_str = "1";

    _menuBar.setCornerWidget(&_label);  // 设置状态标签
    _label.setAlignment(Qt::AlignRight);// 设置标签右对齐
    _label.setText("      当前选择：直线，black，black，1");

    // 连接信号与槽
    connect(&_line, &QAction::triggered, [=](){
        _shape_str = "直线";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_rectangle, &QAction::triggered, [=](){
        _shape_str = "矩形";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_ellipse, &QAction::triggered, [=](){
        _shape_str = "椭圆";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_polygon, &QAction::triggered, [=](){
        _shape_str = "多边形";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_black, &QAction::triggered, [=](){
        _color_A_str = "black";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_red, &QAction::triggered, [=](){
        _color_A_str = "red";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_green, &QAction::triggered, [=](){
        _color_A_str = "green";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_blue, &QAction::triggered, [=](){
        _color_A_str = "blue";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_black, &QAction::triggered, [=](){
        _color_B_str = "black";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_red, &QAction::triggered, [=](){
        _color_B_str = "red";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_green, &QAction::triggered, [=](){
        _color_B_str = "green";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_blue, &QAction::triggered, [=](){
        _color_B_str = "blue";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_width, &QAction::triggered, [=](){
        bool ok;
        _width_str = QInputDialog::getText(this, "线条宽度", "请输入线条宽度", QLineEdit::Normal, "", &ok);
        if(!ok){
            _width_str = "1";
        }
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);

    if(_shape_str == "直线"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(100, 100, 500, 500);
    }
    else if(_shape_str == "矩形"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        painter.drawRect(100, 100, 400, 400);
    }
    else if(_shape_str == "椭圆"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        painter.drawEllipse(100, 100, 400, 400);
    }
    else if(_shape_str == "多边形"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        QVector<QPoint> points;
        // 五角星
        points.push_back(QPoint(200, 50));
        points.push_back(QPoint(250, 200));
        points.push_back(QPoint(400, 200));
        points.push_back(QPoint(300, 300));
        points.push_back(QPoint(350, 450));
        points.push_back(QPoint(200, 350)); // 底部
        points.push_back(QPoint(50, 450));
        points.push_back(QPoint(100, 300));
        points.push_back(QPoint(0, 200));
        points.push_back(QPoint(150, 200));

        painter.drawPolygon(points);
    }

}

MainWindow::~MainWindow(){}
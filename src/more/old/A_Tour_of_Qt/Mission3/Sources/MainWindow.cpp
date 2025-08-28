#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Misson3 飞鸟");
    this -> setFixedSize(600, 800);
    
    QPixmap pixmap("img/bg.jpg");
    pixmap = pixmap.scaled(this -> size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    _background.setParent(this);
    _background.setPixmap(pixmap);
    _background.setGeometry(0, 0, this -> width(), this -> height());

    pixmap.load("img/bird.jpg");
    pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    _bird.setParent(this);
    _bird.setPixmap(pixmap);
    _bird.setGeometry(200, 340, pixmap.width(), pixmap.height());

    pixmap.load("img/za.jpg");
    pixmap = pixmap.scaled(100, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    za.setParent(this);
    za.setPixmap(pixmap);
    za.setGeometry(600, -400, pixmap.width(), pixmap.height());

    pixmap.load("img/za.jpg");
    pixmap = pixmap.scaled(100, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    zb.setParent(this);
    zb.setPixmap(pixmap);
    zb.setGeometry(600, 500, pixmap.width(), pixmap.height());

    // 左上角显示分数
    QLabel *score = new QLabel(this);
    score -> setGeometry(10, 10, 50, 20);
    connect(&_za_t, &QTimer::timeout, [=](){
        score -> setText("分数：" + QString::number(source));
    });

    // 通过定时器实现重力效果
    connect(&_G, &QTimer::timeout, [=](){
        _bird.move(_bird.x(), _bird.y() + acc());
        update();
    });

    // 通过定时器实现跳跃效果
    connect(&_jump, &QTimer::timeout, [=](){
        if(abs(starty - _bird.y()) > 200){  // 跳跃高度
            _jump.stop();

            g=1;    // 每次 start 加速度重置
            _G.start(10);
            return;
        }

        _bird.move(_bird.x(), _bird.y() + bcc());
    });

    connect(&_za_t, &QTimer::timeout, [=](){
        za.move(za.x() - 2, za.y());
        zb.move(zb.x() - 2, zb.y());

        if(za.x() + za.width() < 0){
            int dy = QRandomGenerator::global()->bounded(-200, 200);
            za.move(600, -400 + dy);
            zb.move(600, 500 + dy);
            source++;
        }

        if(ck()){   // 检查碰撞
            _G.stop();
            _jump.stop();
            _za_t.stop();
            flg = false;
            QMessageBox::information(this, "提示", "游戏结束，您的分数为：" + QString::number(source));
            // bird重置
            _bird.move(200, 340);
            // za重置
            za.move(600, -400);
            zb.move(600, 500);
            // 分数重置
            source = 0;
        }
    });
}

MainWindow::~MainWindow(){}

bool MainWindow::ck(){
    if(_bird.x()+_bird.width() >= za.x() && _bird.x() <= za.x() + za.width()){
        if(_bird.y() <= za.y() + za.height() || _bird.y() + _bird.height() >= zb.y()){
            return true;
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event -> key() == Qt::Key_Space){
        
        // 开始游戏
        if(!flg){
            flg=1;
            g=1;
            starty = _bird.y(); // 记录跳跃前的高度
            _G.start(10);
            _za_t.start(10);
        }

        // 跳跃
        if(!_jump.isActive()){ // 在非跳跃状态
            _G.stop();          // 重力停止
            
            starty = _bird.y(); // 记录跳跃前的高度
            
            g=1;
            up=-8;
            _jump.start(10);    // 跳跃开始
        }
        else if(_jump.isActive()){ // 在跳跃状态再跳跃
            //_G.stop();          // 实际上本来就是停止的，这里没必要

            _jump.stop();       // 停止上一次的跳跃
            starty = _bird.y(); // 记录跳跃前的高度
            
            // g=1; 连续跳跃 g 叠加
            up=-8;
            _jump.start(10);    // 重新跳跃
        }
    }
}
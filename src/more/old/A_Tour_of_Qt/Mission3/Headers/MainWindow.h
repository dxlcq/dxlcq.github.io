#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    bool ck();  // 检查是否碰撞
    void keyPressEvent(QKeyEvent *event);

    double g=1;    // 将 g 看作加速度    
    int acc(){
        return std::max(15, (int)(g += 0.2));
    } // 重力加速度，越来越快

    int source = 0; // 记录分数
    double up=-8;
    int bcc(){
        return up += 0.2;
    } // 跳跃加速度，越来越慢

    QLabel  _background,
            _bird,
            za, zb;
    
    QTimer  _G, _jump;  // 重力与跳跃
    QTimer  _za_t;      // 障碍物

    bool flg = false;   // 用于判断是否开始游戏
    int starty=0;       // 记录跳跃前的高度
};
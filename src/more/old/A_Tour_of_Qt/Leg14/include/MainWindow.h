#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QRandomGenerator>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中央部件
    QLabel      _labeltext;
    QTimer      _timer;         // 定时器
};
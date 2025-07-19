#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget; // 中心窗口
    QHBoxLayout     _layout;        // 水平布局
    QProgressBar    _progressBar;   // 进度条
    QPushButton     _button;        // 按钮
};
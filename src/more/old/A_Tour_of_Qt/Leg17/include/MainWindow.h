#pragma once

#include <QMainWindow>
#include <fstream>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QString _words; // 从文件中读取的所有字
    int cnt=0;      // 记录已经打对的字数

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
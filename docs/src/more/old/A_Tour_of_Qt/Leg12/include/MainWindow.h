#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget;
    QLabel      _A, _B;
    QLineEdit   _lineEdit_A_X,
                _lineEdit_A_Y,
                _lineEdit_B_X,
                _lineEdit_B_Y;

    void paintEvent(QPaintEvent *event);
};
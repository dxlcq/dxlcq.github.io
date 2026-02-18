#pragma once

#include <QWidget>
#include <QLayout>
#include <QPushButton>

class MainWindow : public QWidget{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QHBoxLayout layout;

    QPushButton button;
};
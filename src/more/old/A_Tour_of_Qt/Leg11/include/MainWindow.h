#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    void onItemClicked(QListWidgetItem *item);  // 点击列表项

    QWidget     _centralWidget; // 中心窗口
    QHBoxLayout _layout;        // 水平布局
    QListWidget _listWidget;    // 列表窗口
    QStackedWidget _stackedWidget;  // 堆叠窗口

    QWidget     _contextWidget1;// 右侧窗口
    QWidget     _contextWidget2;
    QWidget     _contextWidget3;

    QVBoxLayout _layout1;       // 垂直布局
    QVBoxLayout _layout2;
    QVBoxLayout _layout3;

    QScrollArea _scrollArea1;   // 滚动窗口
    QScrollArea _scrollArea2;
    QScrollArea _scrollArea3;

    QString _str1="", _str2="", _str3="";
    int cnt1=0, cnt2=0, cnt3=0;
};
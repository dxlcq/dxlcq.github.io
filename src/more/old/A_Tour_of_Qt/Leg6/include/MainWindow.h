#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QListWidget>
#include <QLineEdit>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:

    void _onSelect(QListWidgetItem* item);

    QWidget*        _centralWidget; // 中心窗口
    QHBoxLayout*    _layout;        // 水平布局
    QListWidget*    _listWidget;    // 列表
    QLineEdit*      _lineEdit;      // 文本框
};
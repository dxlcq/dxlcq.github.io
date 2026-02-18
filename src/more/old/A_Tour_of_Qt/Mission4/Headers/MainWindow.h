#pragma once

#include <map>

#include <QMainWindow>
#include <QLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QTimer>

#include "../Headers/Client.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     centralWidget;  
    QHBoxLayout centralLayout;
    
    QListWidget _friendList;        // 左边 好友列表
    QVBoxLayout _rightLayout;       // 右边 聊天记录 + 发送
        QStackedWidget _sw;         // 聊天记录 + 发送
        std::map<int, QTextEdit*> _chatRecord;      // 聊天记录
        QHBoxLayout _inputLayout;   // 输入框 + 发送按钮
            QTextEdit _input;       // 输入框
            QPushButton _send;      // 发送按钮

    jiao::Client c;                 // 客户端
};
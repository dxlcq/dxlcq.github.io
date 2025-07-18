#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     *_centralWidget;
    QMenuBar    *_menuBar;   // 菜单栏

    QMenu       *_file;      // 文件
        QAction     *_new;      // 新建
        QAction     *_open;     // 打开

    QMenu       *_help;      // 工具
        QAction     *_about;    // 关于

    void newFile();
    void openFile();
    void about();
};
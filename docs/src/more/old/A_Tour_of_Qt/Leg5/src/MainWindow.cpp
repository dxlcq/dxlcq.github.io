#include "include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    _centralWidget  = new QWidget();
    _menuBar        = new QMenuBar();
    _file           = new QMenu();
        _new        = new QAction();
        _open       = new QAction();
    _help           = new QMenu();
        _about      = new QAction();

    setWindowTitle("Leg 5 菜单与快捷键");
    setCentralWidget(_centralWidget);   // 设置中心窗口
    setMenuBar(_menuBar);               // 设置菜单栏

    _file = _menuBar->addMenu("文件");          // 添加菜单
    
    _new->setText("新建(N)");                   // 设置菜单项
    _new->setShortcut(QKeySequence("Ctrl+N"));  // 设置快捷键
    _file->addAction(_new);

    _open->setText("打开(O)");
    _open->setShortcut(QKeySequence("Ctrl+O"));
    _file->addAction(_open);

    _help = _menuBar->addMenu("帮助");          // 添加菜单
    
    _about->setText("关于(A)");
    _about->setShortcut(QKeySequence("Ctrl+A"));
    _help->addAction(_about);

    connect(_new, &QAction::triggered, this, &MainWindow::newFile);
    connect(_open, &QAction::triggered, this, &MainWindow::openFile);
    connect(_about, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::newFile(){
    QMessageBox::information(this, "新建", "新建文件");
}

void MainWindow::openFile(){
    QMessageBox::information(this, "打开", "打开文件");
}

void MainWindow::about(){
    QMessageBox::information(this, "关于", "Leg 5 菜单与快捷键");
}

MainWindow::~MainWindow(){
    delete _centralWidget;
    delete _menuBar;
    delete _file;
    delete _new;
    delete _open;
    delete _help;
    delete _about;
}
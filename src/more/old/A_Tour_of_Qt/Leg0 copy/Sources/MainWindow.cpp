#include "../Headers/MainWindow.h"
#include "../Headers/Login.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{   
    this -> setWindowTitle("Hello Qt!");
    this -> setLayout(&layout);

    layout.addWidget(&button);
    button.setText("退出登陆");

    connect(&button, &QPushButton::clicked, this, [&](){
        Login *login = new Login();
        login -> show();
        login -> move(this -> pos());
        this -> close();
    });
}

MainWindow::~MainWindow(){}
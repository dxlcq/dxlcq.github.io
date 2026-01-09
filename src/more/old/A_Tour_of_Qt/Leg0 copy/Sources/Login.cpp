#include "../Headers/Login.h"
#include "../Headers/MainWindow.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
{
    this -> setWindowTitle("登陆界面");
    this -> setLayout(&layout);

    layout.addWidget(&username);
    layout.addWidget(&password);
    layout.addWidget(&login);
    login.setText("登陆");

    connect(&login, &QPushButton::clicked, this, [&](){
        if(username.text() == "jiao" && password.text() == "jiao"){
            QMessageBox::information(this, "登陆成功", "登陆成功");
            
            MainWindow *mainWindow = new MainWindow();  // 创建主界面
            mainWindow -> show();                       // 显示主界面
            mainWindow -> move(this -> pos());          // 将主界面移动到登陆界面的位置
            this -> close();                            // 关闭登陆界面
        } else 
            QMessageBox::information(this, "登陆失败", "登陆失败");
    });
}

Login::~Login(){
    
}
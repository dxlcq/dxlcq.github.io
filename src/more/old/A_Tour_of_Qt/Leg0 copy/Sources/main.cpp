#include <QApplication>
#include "../Headers/Login.h"
#include "../Headers/MainWindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Login *login = new Login();
    login->show();
    return app.exec();
}
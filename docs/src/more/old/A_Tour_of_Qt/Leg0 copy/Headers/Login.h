#pragma once

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class Login : public QWidget{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    QVBoxLayout layout;
    QLineEdit   username, password;
    QPushButton login;
};
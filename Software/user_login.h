#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include <QMainWindow>
#include <QMessageBox>

#include <QDialog>

#include "mainwindow.h"
namespace Ui {
class user_login;
}

class user_login : public QMainWindow
{
    Q_OBJECT

public:
    explicit user_login(QWidget *parent = nullptr);
    ~user_login();

private slots:
    void on_loginButton_clicked();

private:
    Ui::user_login *ui;
};

#endif // USER_LOGIN_H

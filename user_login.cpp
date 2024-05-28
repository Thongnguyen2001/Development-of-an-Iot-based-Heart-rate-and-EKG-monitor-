#include "user_login.h"
#include "ui_user_login.h"

user_login::user_login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user_login)
{
    this->show();
    ui->setupUi(this);
}

user_login::~user_login()
{

    delete ui;

}

void user_login::on_loginButton_clicked()
{
    QString UserName = ui->Username->text();
    QString Password = ui->passWord->text();

    if(UserName=="NguyenBaThong" && Password == "@Nbthong2203")
    {
        QMessageBox::information(this,"Hi NguyenBaThong","Login successfully");

        MainWindow mainwindow= new MainWindow();


    }
    else
    {
        QMessageBox::warning(this,"Hi NguyenBaThongh","Please Enter Valid Username or Password");
    }
}



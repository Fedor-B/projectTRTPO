#include "registration.h"
#include "ui_registration.h"

#define person "person"
#define id "id"
#define user "username"
#define pas "password"



Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}



void Registration::on_buttonBox_accepted()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pmg.db3");
    db.open();
    QSqlQuery qry;
    qry.exec("create table " person " ("
                user " QString not null,"
                pas "  QString not null"
                ")"
                );

    QString username = ui->loginEdit->text();
    qry.exec("select username, password from person ");
    bool flag=false;
    while(qry.next()){
        if(qry.value(0).toString() == username){
            flag = true;
            break;
        }
    }
    if(flag == false && ui->passwordEdit->text() == ui->secpassEdit->text()){
        emit open_window();

        QString password = ui->passwordEdit->text();


        qry.prepare("insert into " person "(" user "," pas ") "
                                                           "values (:use, :pass)");
        Cryption object;
        password = object.cryptionpas(password);
        qry.bindValue(":use", username);
        qry.bindValue(":pass", password);
        qry.exec();


        ui->loginEdit->clear();
        ui->passwordEdit->clear();
        ui->secpassEdit->clear();
    }
    else
    {
        if(flag == true)
            QMessageBox::warning(this,"Warning","Такой логин уже существует");
        else
            QMessageBox::warning(this,"Warning","Пароли различаются");
        flag = false;
        this->show();
    }
}



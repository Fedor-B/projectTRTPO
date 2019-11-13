#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("pmg.db3");
    db.open();
    QString login=ui->LoginEdit->text();
    QString password = ui->PasswordEdit->text();
    Cryption object;
    password = object.cryptionpas(password);
    QSqlQuery qry;
    qry.exec("select username, password from person ");
    bool flag=false;
    while(qry.next()){
        if(qry.value(0).toString() == login && qry.value(1).toString() == password)
            flag = true;
    }
    if (flag == false){
        QMessageBox::warning(this,"Ошибка","Такой пользователь не зарегистрирован в системе");
    }
    else{
        view_window = new view;
        view_window->show();
        connect(view_window,&view::open_window,this,&MainWindow::show);
        db.close();
        this->close();
        ui->LoginEdit->clear();
        ui->PasswordEdit->clear();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->LoginEdit->clear();
    ui->PasswordEdit->clear();
    registr = new Registration();
    registr->show();
    connect(registr,&Registration::open_window,this,&MainWindow::show);
    this->close();
}

void MainWindow::on_PasswordEdit_returnPressed()
{
    on_pushButton_clicked();
}

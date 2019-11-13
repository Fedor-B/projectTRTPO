#include "view.h"
#include "ui_view.h"
#include <QTableView>
#include <QDebug>

#define table  "employeers"
#define id  "_id"
#define a  "name"
#define b  "surname"
#define ca  "age_work"


view::view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view)
{
    ui->setupUi(this);

    db.setDatabaseName("employees.db3");
    db.open();
    m = new QSortFilterProxyModel;
    ui->tableView->setModel(m);
    model = new QSqlTableModel;

    model->setEditStrategy(QSqlTableModel::OnRowChange);
    QSqlQuery qry;
    qry.exec("create table " table " ("
             id " integer primary key autoincrement, "
             a " QString not null,"
             b "  QString not null,"
             ca " integer not null"
                ")"
             );
    model->setTable("employeers");


    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Имя"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Фамилия"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Стаж"));

    model->select();
    m->setSourceModel(model);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);
    ui->tableView->setAlternatingRowColors(true);
    ui->radioName->setChecked(true);
    connect(ui->save_but,&QPushButton::clicked,this,&view::save_sql);
}

view::~view()
{
    delete ui;
}


void view::save_sql()
{
    save_as_flag = true;
    model->submitAll();
}



void view::on_back_but_clicked()
{
    if(save_as_flag == false){
        QMessageBox qms;
        qms.setText("Документ был изменен!");
        qms.setInformativeText("Закрыть без сохранения?");
        qms.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        int ret = qms.exec();
        switch(ret){
        case QMessageBox::Save:
            save_sql();
        case QMessageBox::Discard:
            db.close();
            emit open_window();
            this->close();
            break;
        default: break;
        }
    }else{
        db.close();
        emit open_window();
        this->close();
    }

}

void view::on_add_but_clicked()
{
    model->insertRows(model->rowCount(),1);

}

void view::on_pushButton_clicked()
{
    int tmp;
    if(ui->radioName->isChecked()) tmp = 1;
    else
        if(ui->radioSurname->isChecked()) tmp = 2;
        else
            tmp = 3;
    m->setFilterKeyColumn(tmp);
    m->setFilterRegExp(ui->lineEdit->text());
}

void view::on_deletButton_clicked()
{
    model->removeRow(ui->tableView->selectionModel()->currentIndex().row());
    model->submitAll();
}

void view::on_alldeletButton_clicked()
{
    for(int i=0;i<model->rowCount();i++){
    model->removeRow(i);
    }
}

void view::resetflag()
{
    save_as_flag = false;
}

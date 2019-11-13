#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "QSqlQuery"
#include "QtSql/QSqlDatabase"
#include <QtSql>
#include "crypter.h"
#include <QMessageBox>


namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::Registration *ui;
    QSqlDatabase pass;


signals:
    void open_window();

};

#endif // REGISTRATION_H

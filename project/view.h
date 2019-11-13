#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "registration.h"

namespace Ui {
class view;
}

class view : public QMainWindow
{
    Q_OBJECT

public:
    explicit view(QWidget *parent = nullptr);
    ~view();

private:
   QSqlTableModel *model ;
   QSortFilterProxyModel *m;
    Ui::view *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    bool save_as_flag = true;

signals:
    void open_window();

private slots:
    void save_sql();
    void on_back_but_clicked();
    void on_add_but_clicked();
    void on_pushButton_clicked();
    void on_deletButton_clicked();
    void on_alldeletButton_clicked();
    void resetflag();
};

#endif // VIEW_H

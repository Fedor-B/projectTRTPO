#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_PasswordEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    Registration *registr;
    view * view_window;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "roku.h"

#include <QMainWindow>
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BtnOK_clicked();
    void on_BtnUp_clicked();
    void on_BtnDown_clicked();
    void on_BtnLeft_clicked();
    void on_BtnRight_clicked();

    void on_rokuIpEdit_editingFinished();

    void on_getBtn_clicked();

private:
    Ui::MainWindow *ui;
    Roku roku;
    QString last_ipval;
};

#endif // MAINWINDOW_H

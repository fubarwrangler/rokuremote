#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "httphandler.h"

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int httpstatus;
    HttpHandler http;
};

#endif // MAINWINDOW_H

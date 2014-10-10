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
    std::string urlbase = "http://192.168.1.128:8060/keypress/";
    std::string fullurl;


    httpstatus = -1;

    http.doit("http://192.168.1.128:8060/keypress/Up");


    qDebug() << "Status: " << http.httpstatus;
}




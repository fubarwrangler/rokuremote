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



void MainWindow::on_BtnOK_clicked()     { roku.sendKey("Select"); }
void MainWindow::on_BtnUp_clicked()     { roku.sendKey("Up"); }
void MainWindow::on_BtnDown_clicked()   { roku.sendKey("Down"); }
void MainWindow::on_BtnRight_clicked()  { roku.sendKey("Right"); }
void MainWindow::on_BtnLeft_clicked()   { roku.sendKey("Left"); }


void MainWindow::on_rokuIpEdit_editingFinished()
{

    //roku.setIp();
    //roku.testConnectivity();
    qDebug() << "Edit done";
}

void MainWindow::on_getBtn_clicked()
{
    roku.testConnectivity();
    qDebug() << "Test done";
}

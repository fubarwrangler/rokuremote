#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    last_ipval = ui->rokuIpEdit->text();
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
    if (ui->rokuIpEdit->text() == last_ipval)   {
        qDebug() << "Edit done -- no-change";
        return;
    }
    if(roku.setIp(ui->rokuIpEdit->text()) == false) {
        qDebug() << "Roku not found, please change!";
    } else {
        roku.refreshData();
    }

    last_ipval = ui->rokuIpEdit->text();
    qDebug() << "Edit done -- changed";
}

void MainWindow::on_getBtn_clicked()
{
    roku.testConnectivity();
    qDebug() << "Test done";
}

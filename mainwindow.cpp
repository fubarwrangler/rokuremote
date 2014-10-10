#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>


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
    QEventLoop loop;

    httpstatus = -1;

    fullurl = urlbase + "Up";

    QUrl url(fullurl.data());
    QNetworkAccessManager  *manager = new QNetworkAccessManager(this);
    QNetworkRequest *req = new QNetworkRequest(url);
    req->setHeader(QNetworkRequest::ContentTypeHeader,
                   QVariant("application/x-www-form-urlencoded"));
    QNetworkReply *reply = manager->post(*req, QByteArray(""));

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(requestEnded(QNetworkReply *)));
    loop.exec();


    qDebug() << "Status: " << httpstatus;
}

void MainWindow::requestEnded(QNetworkReply *reply)
{

    qDebug() << "Ended\n";

    httpstatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    switch(reply->error())  {
    case QNetworkReply::NoError:
        qDebug() << "Ok\n";
        break;
    default:
        qDebug() << "Error\n";
        break;

    }

}


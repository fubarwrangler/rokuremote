#include "httphandler.h"

#include <QEventLoop>

HttpHandler::HttpHandler(QObject *parent) :
    QObject(parent)
{
    status = -1;
}

void HttpHandler::post(std::string &path, bool synchronous)
{
    post(path.data(), synchronous);
}

void HttpHandler::post(QString &path, bool synchronous)
{
    post(path.toLocal8Bit().data(), synchronous);
}

void HttpHandler::post(const char *path, bool synchronous)
{
    QEventLoop *loop;
    QNetworkReply *reply;
    QNetworkRequest req = QNetworkRequest(url);

    url.setUrl(QString(path));
    qDebug() << "Set url: " << path;

    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/x-www-form-urlencoded"));
    reply = manager.post(req, QByteArray(""));

    if(synchronous) {
        loop = new QEventLoop;
        QObject::connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    }
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(requestEnded(QNetworkReply *)));
    if(synchronous) {
        loop->exec();
        delete loop;
    }

    qDebug() << "Donzo";

}

void HttpHandler::requestEnded(QNetworkReply *reply)
{

    qDebug() << "Ended\n";

    status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "Status - " << status;
    switch(reply->error())  {
    case QNetworkReply::NoError:
        qDebug() << "Ok\n";
        break;
    default:
        qDebug() << "Error: " << reply->errorString();
        break;

    }

    reply->deleteLater();
}



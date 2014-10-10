#include "httphandler.h"

#include <QEventLoop>

HttpHandler::HttpHandler(QObject *parent) :
    QObject(parent)
{
    httpstatus = -1;
}

void HttpHandler::doit(const char *path)
{
    url.setUrl(QString(path));
    QNetworkReply *reply;
    QNetworkRequest req = QNetworkRequest(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/x-www-form-urlencoded"));
    reply = manager.post(req, QByteArray(""));

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(requestEnded(QNetworkReply *)));
    loop.exec();
    qDebug() << "Donzo";
}

void HttpHandler::requestEnded(QNetworkReply *reply)
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



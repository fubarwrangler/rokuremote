#include "httphandler.h"

#include <QEventLoop>

HttpHandler::HttpHandler(QObject *parent) :
    QObject(parent)
{
    status = -1;
}

void HttpHandler::post(QUrl &url, bool synchronous)
{
    QEventLoop *loop;
    QNetworkRequest *req;

    req = new QNetworkRequest(url);

    req->setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/x-www-form-urlencoded"));
    reply = manager.post(*req, QByteArray(""));
    if(synchronous) {
        loop = new QEventLoop;

        QObject::connect(reply, SIGNAL(finished()), loop, SLOT(quit()));

    }
    //QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(requestEnded(QNetworkReply *)));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(requestEnded()));
    if(synchronous) {
        loop->exec();
        delete loop;
    }

    delete req;
    qDebug() << "Donezo";

}

void HttpHandler::post(std::string &path, bool synchronous)
{
    post(path.data(), synchronous);
}

void HttpHandler::post(QString &path, bool synchronous)
{
    QUrl url = QUrl(path);
    post(url, synchronous);
}

void HttpHandler::post(const char *path, bool synchronous)
{
    QString str = QString(path);
    post(str, synchronous);
}

void HttpHandler::requestEnded(void)
{
    status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch(reply->error())  {
    case QNetworkReply::NoError:
        qDebug() << "Status - Ok - " << status;
        break;
    default:
        qDebug() << "Status - Error - " << status << " - " << reply->errorString();
        break;

    }
    reply->deleteLater();
    reply = 0;
}



#include "httphandler.h"

#include <QEventLoop>

HttpHandler::HttpHandler(QObject *parent) :
    QObject(parent)
{
    status = -1;
    qnam = new QNetworkAccessManager(this);
}

HttpHandler::~HttpHandler()
{
    delete qnam;
}

void HttpHandler::post(QUrl &url, bool synchronous)
{
    QEventLoop *loop;
    QNetworkRequest *req;
    QNetworkReply *reply;

    req = new QNetworkRequest(url);

    req->setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/x-www-form-urlencoded"));
    reply = qnam->post(*req, QByteArray(""));
    if(synchronous) {
        loop = new QEventLoop;

        QObject::connect(reply, SIGNAL(finished()), loop, SLOT(quit()));

    }
    //QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(requestEnded(QNetworkReply *)));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(PostRequestEnded()));
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

QByteArray HttpHandler::get(std::string &url)
{
    return get(url.data());
}

QByteArray HttpHandler::get(const char *path)
{
    QUrl url = QUrl(QString(path));
    return get(url);
}

QByteArray HttpHandler::get(QUrl &url)
{
    QEventLoop loop;
    QNetworkReply *reply;

    reply = qnam->get(QNetworkRequest(url));

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //QObject::connect(qnam, SIGNAL(finished(QNetworkReply *)), this, SLOT(GetRequestEnded(QNetworkReply *)));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(GetRequestEnded()));
    loop.exec();

    qDebug() << "Get Done";

    return response;
}

void HttpHandler::GetRequestEnded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    switch(reply->error())  {
    case QNetworkReply::NoError:
        qDebug() << "Status - Ok - " << status;
        break;
    default:
        qDebug() << "Status - Error - " << status << " - " << reply->errorString();
        break;

    }

    response = reply->readAll();
    qDebug() << "read reply - " << response;

    reply->deleteLater();
}



void HttpHandler::PostRequestEnded(void)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

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
}



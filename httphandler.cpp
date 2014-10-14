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

    reply = qnam->get(QNetworkRequest(url));

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(GetRequestEnded()));
    loop.exec();

    qDebug() << "Get Done";

    return response;
}

void HttpHandler::GetRequestEnded(void)
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

    response = reply->readAll();
    reply->deleteLater();
    reply = 0;
}



void HttpHandler::PostRequestEnded(void)
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



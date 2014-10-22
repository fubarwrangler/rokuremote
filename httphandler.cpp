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

QByteArray HttpHandler::post(QUrl &url)
{
    QNetworkRequest *req;
    QNetworkReply *reply;
    QEventLoop loop;

    req = new QNetworkRequest(url);

    req->setHeader(QNetworkRequest::ContentTypeHeader,
                  QVariant("application/x-www-form-urlencoded"));
    reply = qnam->post(*req, QByteArray(""));


    QObject::connect(reply, SIGNAL(finished()), this, SLOT(PostRequestEnded()));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    delete req;
    qDebug() << "read reply - " << response;
    return response;

}

QByteArray HttpHandler::post(std::string &path)
{
    return post(path.data());
}

QByteArray HttpHandler::post(QString &path)
{
    QUrl url = QUrl(path);
    return post(url);
}

QByteArray HttpHandler::post(const char *path)
{
    QString str = QString(path);
    return post(str);
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
    response = reply->readAll();
    qDebug() << "Post reply read";
    reply->deleteLater();
}

QByteArray HttpHandler::get(QUrl &url)
{
    QEventLoop loop;
    QNetworkReply *reply;

    reply = qnam->get(QNetworkRequest(url));

    QObject::connect(reply, SIGNAL(finished()), this, SLOT(GetRequestEnded()));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    qDebug() << "Get Done";

    return response;
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

QByteArray HttpHandler::get(QString &path)
{
    QUrl url = QUrl(path);
    return get(url);
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
        qDebug() << "Status - Error - " << status << reply->error() << " - " << reply->errorString();
        break;

    }

    response = reply->readAll();
    qDebug() << "read reply - " << response;

    reply->deleteLater();
}



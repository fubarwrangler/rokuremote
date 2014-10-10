#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QEventLoop>
#include <QDebug>



class HttpHandler : public QObject
{
    Q_OBJECT

public:
    explicit HttpHandler(QObject *parent = 0);
    void doit(const char *path);
    int httpstatus;
private slots:
    void requestEnded(QNetworkReply *reply);
private:
    QNetworkAccessManager manager;
    QEventLoop loop;
    QUrl url;
};

#endif // HTTPHANDLER_H

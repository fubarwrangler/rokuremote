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
    void post(const char *path, bool synchronous = true);
    void post(std::string &path, bool synchronous = true);
    void post(QString &path, bool synchronous);
    int status;
private slots:
    void requestEnded(QNetworkReply *reply);
private:
    QNetworkAccessManager manager;
    QEventLoop loop;
    QUrl url;
};

#endif // HTTPHANDLER_H

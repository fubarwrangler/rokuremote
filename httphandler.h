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
    void post(const char *path, bool synchronous = false);
    void post(std::string &path, bool synchronous = false);
    void post(QString &path, bool synchronous = false);
    void post(QUrl &url, bool synchronous = false);
    int status;
private slots:
    void requestEnded(void);
private:
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply;
};

#endif // HTTPHANDLER_H

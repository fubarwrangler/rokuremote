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
    ~HttpHandler();

    void post(const char *path, bool synchronous = false);
    void post(std::string &path, bool synchronous = false);
    void post(QString &path, bool synchronous = false);
    void post(QUrl &url, bool synchronous = false);

    QByteArray get(QUrl &url);
    QByteArray get(const char *path);
    QByteArray get(std::string &url);

    int status;
private slots:
    void PostRequestEnded(void);
    void GetRequestEnded(void);
private:
    QNetworkAccessManager *qnam;
    QNetworkReply *reply;
    QByteArray response;
};

#endif // HTTPHANDLER_H

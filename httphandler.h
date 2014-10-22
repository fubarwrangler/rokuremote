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

    QByteArray post(const char *path);
    QByteArray post(std::string &path);
    QByteArray post(QString &path);
    QByteArray post(QUrl &url);

    QByteArray get(const char *path);
    QByteArray get(QUrl &url);
    QByteArray get(std::string &url);
    QByteArray get(QString &path);

    int status;
private slots:
    void PostRequestEnded(void);
    void GetRequestEnded();
private:
    QNetworkAccessManager *qnam;
    //QNetworkReply *reply;
    QByteArray response;
};

#endif // HTTPHANDLER_H

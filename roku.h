#ifndef ROKU_H
#define ROKU_H

#include <httphandler.h>
#include <QHostAddress>
#include <QHostInfo>


class Roku
{
public:
    explicit Roku(QString addr);
    void sendKey(const char *name);
    void testConnectivity(void);
    bool refreshData(void);
    bool setIp(const QString &str);
    QString modelname;
    QString modelnum;
    QString serial;

private:
    QString genUrl(void);
    void parseModelData(const QByteArray &bytes);
    HttpHandler http;
    QString address;
    int port;
    int num_req;
};

#endif // ROKU_H

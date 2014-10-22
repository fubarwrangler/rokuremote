#include "roku.h"
#include <stdio.h>
#include <QDebug>

Roku::Roku(void)
{
    //address = QString("192.168.1.128");
    address = QString("127.0.0.1");
    port = 8060;
    num_req = 0;
}

void Roku::testConnectivity(void)
{
    QString url = genUrl();
    QByteArray foo = http.get(url);
    qDebug() << "Get reply: " << foo.constData();
}

void Roku::sendKey(const char *name)
{

    QString url = genUrl() + "/keypress/" + name;
    http.post(url);
}

QString Roku::genUrl(void)
{
    QString portstr;
    portstr.setNum(port);
    QString url = "http://" + address + ":" + portstr;
    return url;
}

bool Roku::refreshData(void)
{
    QString url = genUrl();
    QByteArray foo = http.get(url);
    qDebug() << "Got data: " << foo;
    return true;
}

bool Roku::setIp(const QString &str)
{
    qDebug() << "Address changed: " << address << " --> " << str;
    address = str;
    return refreshData();
}


#include "roku.h"
#include <stdio.h>
#include <QDebug>
#include <QXmlStreamReader>
#include <iostream>

Roku::Roku(QString addr)
{
    address = addr;
    port = 8060;
    num_req = 0;
    modelname = "no model";
    modelnum = "no num";
    serial = "###";
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


void Roku::parseModelData(const QByteArray &bytes)  {
    QXmlStreamReader xml(bytes);

    while (!xml.atEnd()) {
          if(xml.readNextStartElement())    {
              if(xml.name() == "modelName") {
                  modelname = QString(xml.readElementText());
              } else if(xml.name() == "modelNumber") {
                  modelnum = QString(xml.readElementText());
              } else if(xml.name() == "serialNumber") {
                  serial = QString(xml.readElementText());
              }
          }
    }
    if (xml.hasError()) {
          qDebug() << "Error reading XML";
    }
}

bool Roku::refreshData(void)
{
    QString url = genUrl();
    QByteArray foo = http.get(url);
    // qDebug() << "Got data: " << foo;
    parseModelData(foo);

    return true;
}

bool Roku::setIp(const QString &str)
{
    qDebug() << "Address changed: " << address << " --> " << str;
    address = str;
    return refreshData();
}


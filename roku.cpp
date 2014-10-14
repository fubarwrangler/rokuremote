#include "roku.h"
#include <stdio.h>
#include <QDebug>

Roku::Roku(void)
{
    //address = "192.168.1.128";
    address = "127.0.0.1";
    port = 8060;
    num_req = 0;
}

void Roku::sendKey(const char *name)
{

    std::string url;
    url = "http://" + address + ":8060/keypress/" + name;
    qDebug() << "Pre url: " << url.data();
    http.post(url);
    num_req += 1;
    qDebug() << "Num: " << num_req;
}
/*
std::string Roku::genUrl(void)
{
    char p[16];
    sprintf(p, "%d", port);
    std::string s = "http://" + address + ":" + p;
    return s;
}*/

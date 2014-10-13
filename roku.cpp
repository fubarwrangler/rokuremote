#include "roku.h"
#include <stdio.h>

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
    http.post(url, false);
    num_req += 1;
    qDebug() << num_req;
}
/*
std::string Roku::genUrl(void)
{
    char p[16];
    sprintf(p, "%d", port);
    std::string s = "http://" + address + ":" + p;
    return s;
}*/

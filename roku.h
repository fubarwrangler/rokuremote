#ifndef ROKU_H
#define ROKU_H

#include <httphandler.h>

class Roku
{
public:
    explicit Roku(void);
    void sendKey(const char *name);
    void testConnectivity(void);

private:
    std::string genUrl(void);
    HttpHandler http;
    std::string address;
    int port;
    int httpstatus;
    int num_req;
};

#endif // ROKU_H

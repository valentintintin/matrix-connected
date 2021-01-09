#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <MD_Parola.h>

#include "Orchestror.h"

class WebServer {

public:
    explicit WebServer(MD_Parola* matrix, Orchestror* orchestror);
    ~WebServer();

    void begin();

    AsyncWebServer server;
    DNSServer dns;

private:
};

#endif
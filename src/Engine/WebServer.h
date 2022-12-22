#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <MD_Parola.h>
#include <AsyncElegantOTA.h>
#include <NtpClientLib.h>

#include "Orchestror.h"

class WebServer {

public:
    explicit WebServer(System* system);

    void begin();

    AsyncWebServer server;
    DNSServer dns;

private:
};

#endif
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <ESP8266WebServer.h>
#include "Screen.h"

class WebServer {

public:
    WebServer(Screen *screen);

    ~WebServer();

    void begin();

private:
    AsyncWebServer server;
};

#endif
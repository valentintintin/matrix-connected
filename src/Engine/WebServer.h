#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Slides/SlideTimer.h>
#include <Slides/SlideCountdown.h>
#include "Screen.h"

class WebServer {

public:
    WebServer(Screen *screen);

    ~WebServer();

    void begin();

private:
    SlideTimer slideTimer;
    SlideCountdown slideCountdown;

    AsyncWebServer server;
};

#endif
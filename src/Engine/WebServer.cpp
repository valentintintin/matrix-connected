#include <Slides/SlideMessage.h>
#include <NtpClientLib.h>
#include "WebServer.h"

WebServer::WebServer(Screen *screen) : server(AsyncWebServer(80)), slideCountdown(SlideCountdown(screen)),
                                       slideTimer(SlideTimer(screen)) {
    server.on("/message/add", HTTP_GET, [screen](AsyncWebServerRequest *request) {
        if (request->hasArg("msg") && request->arg("msg").length() > 0) {
            screen->addSlide(new SlideMessage(screen, request->arg("msg")));
            request->send(201, F("text/plain"), F("OK"));
        } else {
            request->send(400, F("text/plain"), F("Missing msg parameter in query"));
        }
    });

    server.on("/timer/start", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        slideTimer.restart();
        screen->setMainSlide(&slideTimer);
        request->send(201, F("text/plain"), F("OK"));
    });

    server.on("/timer/restart", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        slideTimer.start();
        screen->setMainSlide(&slideTimer);
        request->send(201, F("text/plain"), F("OK"));
    });

    server.on("/timer/stop", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        slideTimer.stop();
        screen->setMainSlide(nullptr);
        request->send(200, F("text/plain"), F("OK"));
    });

    server.on("/countdown/start", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        if (request->hasArg(F("duration"))) {
            slideCountdown.restart((uint64_t) request->arg(F("duration")).toInt());
            screen->setMainSlide(&slideCountdown);
            request->send(201, F("text/plain"), F("OK"));
        } else {
            uint64_t toDate = request->hasArg(F("day")) ? request->arg(F("day")).toInt() * 88400 : 0;
            toDate += request->hasArg(F("hour")) ? request->arg(F("hour")).toInt() * 3600 : 0;
            toDate += request->hasArg(F("minute")) ? request->arg(F("minute")).toInt() * 60 : 0;
            toDate += request->hasArg(F("second")) ? request->arg(F("second")).toInt() : 0;
            if (toDate > 0) {
                slideCountdown.restart(toDate);
                screen->setMainSlide(&slideCountdown);
                request->send(201, F("text/plain"), F("OK"));
            } else {
                request->send(400, F("text/plain"), F("Missing state parameter in query (on|off)"));
            }
        }
    });

    server.on("/countdown/restart", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        slideCountdown.start();
        screen->setMainSlide(&slideCountdown);
        request->send(201, F("text/plain"), F("OK"));
    });

    server.on("/countdown/stop", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        slideCountdown.stop();
        screen->setMainSlide(nullptr);
        request->send(200, F("text/plain"), F("OK"));
    });

    server.on("/state", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        if (request->hasArg(F("state"))) {
            screen->setState(request->arg(F("state")).equalsIgnoreCase(F("on")));
            request->send(200, F("text/plain"), F("OK"));
        } else {
            request->send(400, F("text/plain"), F("Missing duration parameter in query"));
        }
    });

    server.on("/ram", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, F("text/plain"), String(ESP.getFreeHeap()));
    });

    server.on("/ram2", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, F("text/plain"), String(ESP.getHeapFragmentation()));
    });

    server.on("/uptime", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        request->send(200, F("text/plain"), NTP.getUptimeString());
    });

    server.on("/notify", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        screen->setBlink();
        if (request->hasArg(F("song")) && request->arg(F("song")).equalsIgnoreCase(F("on"))) {
            screen->setSongToPlay(dangoSong);
        }
        request->send(201, F("text/plain"), F("OK"));
    });

    server.on("/song", HTTP_GET, [screen, this](AsyncWebServerRequest *request) { // used to debug --> memory leak
        if (request->hasArg(F("song"))) {
            screen->setSongToPlay(request->arg(F("song")).c_str());
            request->send(201, F("text/plain"), F("OK"));
        } else {
            request->send(400, F("text/plain"), F("Missing song parameter in query"));
        }
        request->send(201, F("text/plain"), F("OK"));
    });

    server.on("/intensity", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
        if (request->hasArg(F("val"))) {
            screen->matrix.setIntensity((byte) request->arg(F("val")).toInt());
            request->send(201, F("text/plain"), F("OK"));
        } else {
            request->send(400, F("text/plain"), F("Missing val parameter in query"));
        }
        request->send(201, F("text/plain"), F("OK"));
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, F("text/plain"), F("Not found"));
    });
}

WebServer::~WebServer() {
}

void WebServer::begin() {
    server.begin();
}
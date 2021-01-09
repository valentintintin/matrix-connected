#include <NtpClientLib.h>
#include <Applets/AppletMessage.h>
#include "WebServer.h"

WebServer::WebServer(MD_Parola* matrix, Orchestror* orchestror) : server(AsyncWebServer(80)) {
    server.on("/message/add", HTTP_GET, [orchestror](AsyncWebServerRequest *request) {
        if (request->hasArg("msg") && request->arg("msg").length() > 0) {
            orchestror->addApplet(new AppletMessage(0, request->arg("msg")));
            request->send(201, F("text/plain"), F("OK"));
        } else {
            request->send(400, F("text/plain"), F("Missing msg parameter in query"));
        }
    });

//    server.on("/timer/start", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        slideTimer.restart();
//        screen->setMainApplet(&slideTimer);
//        request->send(201, F("text/plain"), F("OK"));
//    });
//
//    server.on("/timer/restart", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        slideTimer.start();
//        screen->setMainApplet(&slideTimer);
//        request->send(201, F("text/plain"), F("OK"));
//    });
//
//    server.on("/timer/stop", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        slideTimer.stop();
//        screen->setMainApplet(nullptr);
//        request->send(200, F("text/plain"), F("OK"));
//    });
//
//    server.on("/countdown/start", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        if (request->hasArg(F("duration"))) {
//            slideCountdown.restart((uint64_t) request->arg(F("duration")).toInt());
//            screen->setMainApplet(&slideCountdown);
//            request->send(201, F("text/plain"), F("OK"));
//        } else {
//            uint64_t toDate = request->hasArg(F("day")) ? request->arg(F("day")).toInt() * 88400 : 0;
//            toDate += request->hasArg(F("hour")) ? request->arg(F("hour")).toInt() * 3600 : 0;
//            toDate += request->hasArg(F("minute")) ? request->arg(F("minute")).toInt() * 60 : 0;
//            toDate += request->hasArg(F("second")) ? request->arg(F("second")).toInt() : 0;
//            if (toDate > 0) {
//                slideCountdown.restart(toDate);
//                screen->setMainApplet(&slideCountdown);
//                request->send(201, F("text/plain"), F("OK"));
//            } else {
//                request->send(400, F("text/plain"), F("Missing state parameter in query (on|off)"));
//            }
//        }
//    });
//
//    server.on("/countdown/restart", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        slideCountdown.start();
//        screen->setMainApplet(&slideCountdown);
//        request->send(201, F("text/plain"), F("OK"));
//    });
//
//    server.on("/countdown/stop", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        slideCountdown.stop();
//        screen->setMainApplet(nullptr);
//        request->send(200, F("text/plain"), F("OK"));
//    });
//
    server.on("/state", HTTP_GET, [orchestror](AsyncWebServerRequest *request) {
        if (request->hasArg(F("state"))) {
            orchestror->setState(request->arg(F("state")).equalsIgnoreCase(F("on")));
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

    server.on("/uptime", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, F("text/plain"), NTP.getUptimeString());
    });
//
//    server.on("/notify", HTTP_GET, [screen, this](AsyncWebServerRequest *request) {
//        screen->setBlink();
//        if (request->hasArg(F("song")) && request->arg(F("song")).equalsIgnoreCase(F("on"))) {
//            screen->setSongToPlay(dangoSong);
//        }
//        request->send(201, F("text/plain"), F("OK"));
//    });
//
//    server.on("/song", HTTP_GET, [screen, this](AsyncWebServerRequest *request) { // used to debug --> memory leak
//        if (request->hasArg(F("song"))) {
//            screen->setSongToPlay(request->arg(F("song")).c_str());
//            request->send(201, F("text/plain"), F("OK"));
//        } else {
//            request->send(400, F("text/plain"), F("Missing song parameter in query"));
//        }
//        request->send(201, F("text/plain"), F("OK"));
//    });
//
    server.on("/intensity", HTTP_GET, [matrix](AsyncWebServerRequest *request) {
        if (request->hasArg(F("val"))) {
            matrix->setIntensity(request->arg(F("val")).toInt());
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

WebServer::~WebServer() = default;

void WebServer::begin() {
    DPRINTLN(F("[WEB SERVER]Start"));
    server.begin();
}

#include <NtpClientLib.h>

#include "Applets/AppletMessage.h"
#include "WebServer.h"

WebServer::WebServer(System* system) : server(AsyncWebServer(80)) {
    Orchestror* orchestror = system->getOrchestorForZone(ZONE_RIGHT);

    server.on("/message/add", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/message/add\t"));
        if (request->hasArg("msg") && request->arg("msg").length() > 0) {
            String msg = request->arg("msg");
            DPRINT(F("Msg: ")); DPRINTLN(msg);
            system->getAppletMessage()->addMessage(msg);
            request->send(201, F("text/plain"), F("OK"));
        } else {
            DPRINTLN("Missing msd parameter");
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
//    server.on("/countdown/start", HTTP_GET, [orchestror](AsyncWebServerRequest *request) {
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
//                request->send(400, F("text/plain"), F("Missing matrixActivated parameter in query (on|off)"));
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
    server.on("/state", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/matrixActivated\t"));
        if (request->hasArg(F("state"))) {
            bool state = request->arg(F("state<")).equalsIgnoreCase(F("on"));
            DPRINT(F("State: ")); DPRINTLN(state);
            system->setMatrixActivated(state);
            request->send(200, F("text/plain"), F("OK"));
        } else {
            DPRINTLN("Missing duration parameter");
            request->send(400, F("text/plain"), F("Missing duration parameter in query"));
        }
    });

    server.on("/ram", HTTP_GET, [](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/ram"));
        request->send(200, F("text/plain"), String(ESP.getFreeHeap()));
    });

    server.on("/ram2", HTTP_GET, [](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/ram2"));
        request->send(200, F("text/plain"), String(ESP.getHeapFragmentation()));
    });

    server.on("/uptime", HTTP_GET, [](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/uptime"));
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
    server.on("/intensity", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/intensity\t"));
        if (request->hasArg(F("val"))) {
            byte val = (byte) request->arg(F("val")).toInt();
            DPRINT(F("Val: ")); DPRINTLN(val);
            system->getMatrix()->setIntensity(val);
            request->send(201, F("text/plain"), F("OK"));
        } else {
            DPRINTLN("Missing val parameter");
            request->send(400, F("text/plain"), F("Missing val parameter in query"));
        }
        request->send(201, F("text/plain"), F("OK"));
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]Not found\t"));
        request->send(404, F("text/plain"), F("Not found"));
    });
}

WebServer::~WebServer() = default;

void WebServer::begin() {
    DPRINTLN(F("[WEB SERVER]Start"));
    server.begin();
}

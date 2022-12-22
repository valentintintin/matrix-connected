#include "Applets/AppletCountdown.h"
#include "WebServer.h"

WebServer::WebServer(System* system) : server(AsyncWebServer(80)) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });

    server.on("/message/add", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/message/add\t"));

        if (request->hasArg("msg") && request->arg("msg").length() > 0) {
            String msg = request->arg("msg");
            DPRINT(F("Msg: ")); DPRINTLN(msg);

            if (system->addMessage(msg)) {
                request->send(201, F("application/json"), F("true"));
            } else {
                request->send(500, F("text/plain"), F("Impossible to get applet"));
                return;
            }
        } else {
            DPRINTLN("Missing msd parameter");
            request->send(400, F("text/plain"), F("Missing msg parameter in query"));
        }
    });

    server.on("/countdown/start", HTTP_GET, [system](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getOrchestorForZone(ZONE);
        Applet* applet = orchestror->getAppletByType(COUNTDOWN);
        if (applet != nullptr) {
            if (request->hasArg(F("restart"))) {
                ((AppletCountdown *) applet)->stopTimer(true);
            } else {
                request->send(403, F("text/plain"), F("There is already a countdown. Stop it before add a new one"));
                return;
            }
        }

        bool songAtTheEnd = !request->hasArg(F("noSongAtTheEnd"));

        if (request->hasArg(F("duration"))) {
            orchestror->addApplet(new AppletCountdown(orchestror, (uint64_t) request->arg(F("duration")).toInt(), request->arg(F("name")), songAtTheEnd));
            request->send(201, F("application/json"), F("true"));
        } else {
            uint64_t toDate = request->hasArg(F("day")) ? request->arg(F("day")).toInt() * 86400 : 0;
            toDate += request->hasArg(F("hour")) ? request->arg(F("hour")).toInt() * 3600 : 0;
            toDate += request->hasArg(F("minute")) ? request->arg(F("minute")).toInt() * 60 : 0;
            toDate += request->hasArg(F("second")) ? request->arg(F("second")).toInt() : 0;
            if (toDate > 0) {
                orchestror->addApplet(new AppletCountdown(orchestror, toDate, request->arg(F("name")), songAtTheEnd));
                request->send(201, F("application/json"), F("true"));
            } else {
                request->send(400, F("text/plain"), F("Missing duration or day/hour/minute/second/duration(sec) or name(optional) parameter in query"));
            }
        }
    });

    server.on("/countdown/stop", HTTP_GET, [system](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getOrchestorForZone(ZONE);
        Applet* applet = orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, F("text/plain"), F("Impossible to get applet"));
            return;
        }

        ((AppletCountdown*) applet)->stopTimer(true);
        request->send(200, F("application/json"), F("true"));
    });

    server.on("/state", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/matrixActivated\t"));
        if (request->hasArg(F("state"))) {
            bool state = request->arg(F("state")).equalsIgnoreCase(F("on"));
            DPRINT(F("State: ")); DPRINTLN(state);
            system->setMatrixActivated(state);
            request->send(200, F("application/json"), F("true"));
        } else {
            DPRINTLN("Missing duration parameter");
            request->send(400, F("text/plain"), F("Missing state parameter in query (on|off)"));
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

    server.on("/notify/dong", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/dong\t"));
        system->dong();
        request->send(200, F("application/json"), F("true"));
    });

    server.on("/notify/song", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/song\t"));
        system->notify();
        request->send(200, F("application/json"), F("true"));
    });

    server.on("/notify/alert", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/alert\t"));
        system->alert();
        request->send(200, F("application/json"), F("true"));
    });

    server.on("/message/date", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/message/date\t"));
        system->showDateMessage();
        request->send(200, F("application/json"), F("true"));
    });

    server.on("/intensity", HTTP_GET, [system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/intensity\t"));
        if (request->hasArg(F("val"))) {
            byte val = (byte) request->arg(F("val")).toInt();
            DPRINT(F("Val: ")); DPRINTLN(val);
            system->setMatrixIntensity(val);
            request->send(201, F("application/json"), F("true"));
        } else {
            DPRINTLN("Missing val parameter");
            request->send(400, F("text/plain"), F("Missing val parameter in query"));
        }
        request->send(201, F("application/json"), F("true"));
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]Not found\t"));
        request->send(404, F("text/plain"), F("Not found"));
    });
}

void WebServer::begin() {
    DPRINTLN(F("[WEB SERVER]Start"));
    SPIFFS.begin();
    AsyncElegantOTA.begin(&server);
    server.begin();
}

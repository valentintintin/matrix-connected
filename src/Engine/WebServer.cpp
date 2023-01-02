#include <LittleFS.h>
#include "Applets/AppletCountdown.h"
#include "WebServer.h"
#include "Applets/AppletMessageLoop.h"

WebServer::WebServer(System* system) : server(AsyncWebServer(80)) {
    const String& json = F("application/json");
    const String& trueStr = F("true");
    const String& trueJson = F("\"true\"");
    const String& falseJson = F("\"false\"");
    const __FlashStringHelper* durationArg = F("duration");
    const __FlashStringHelper* restartArg = F("restart");
    const __FlashStringHelper* valArg = F("val");
    const __FlashStringHelper* msgArg = F("msg");

    server.on(PSTR("/"), HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, F("/index.html"));
    });

    server.on(PSTR("/message/add"), HTTP_GET, [msgArg, restartArg, json, trueJson, falseJson, system, durationArg](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/message/add\t"));

        if (request->hasArg(msgArg) && request->arg(msgArg).length() > 0) {
            String msg = request->arg(msgArg);
            DPRINT(F("Msg: ")); DPRINTLN(msg);

            unsigned long duration = 0;
            if (request->hasArg(durationArg)) {
                duration = (unsigned long) request->arg(durationArg).toInt();
                DPRINT(F("Duration: ")); DPRINTLN((unsigned long) duration);
            }

            if (duration > 0) {
                Orchestror* orchestror = system->getMainOrchestor();
                Applet* applet = orchestror->getAppletByType(MESSAGE_LOOP);
                if (applet != nullptr) {
                    if (request->hasArg(restartArg)) {
                        ((AppletMessageLoop *) applet)->stopTimer();
                    } else {
                        request->send(403, json, F("\"There is already a message loop. Stop it before add a new one\""));
                        return;
                    }
                }

                bool result = orchestror->addApplet(
                    new AppletMessageLoop(orchestror, request->arg(msgArg).c_str(), duration)
                );
                request->send(result ? 201 : 500, json, result ? trueJson : falseJson);
            } else {
                if (system->addMessage(msg.c_str())) {
                    request->send(201, json, trueJson);
                } else {
                    request->send(500, json, F("\"Impossible to get applet\""));
                }
            }
        } else {
            DPRINTLN("Missing msd parameter");
            request->send(400, json, F("\"Missing msg parameter in query\""));
        }
    });

    server.on(PSTR("/message/loop/stop"), HTTP_GET, [system, json, trueJson](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        Applet* applet = orchestror->getAppletByType(MESSAGE_LOOP);
        if (applet == nullptr) {
            request->send(500, json, F("\"Impossible to get applet\""));
            return;
        }

        ((AppletMessageLoop*) applet)->stopTimer();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/countdown/start"), HTTP_GET, [msgArg, restartArg, json, trueJson, system, durationArg](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        Applet* applet = orchestror->getAppletByType(COUNTDOWN);
        if (applet != nullptr) {
            if (request->hasArg(restartArg)) {
                orchestror->destroyApplet(applet);
            } else {
                request->send(403, json, F("\"There is already a countdown. Stop it before add a new one\""));
                return;
            }
        }

        bool songAtTheEnd = !request->hasArg(F("noSongAtTheEnd"));

        if (request->hasArg(durationArg)) {
            orchestror->addApplet(new AppletCountdown(orchestror, (unsigned long) request->arg(durationArg).toInt(), request->arg(msgArg).c_str(), songAtTheEnd));
            request->send(201, json, trueJson);
        } else {
            request->send(400, json, F("\"Missing duration(sec) or msg(optional) parameter in query\""));
        }
    });

    server.on(PSTR("/countdown/stop"), HTTP_GET, [system, json, trueJson](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        Applet* applet = orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, json, F("\"Impossible to get applet\""));
            return;
        }

        orchestror->destroyApplet(applet);
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/state"), HTTP_GET, [valArg, system, json, trueJson, trueStr](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/matrixActivated\t"));
        if (request->hasArg(valArg)) {
            bool state = request->arg(valArg).equalsIgnoreCase(trueStr);
            DPRINT(F("State: ")); DPRINTLN(state);
            system->setMatrixActivated(state);
            request->send(200, json, trueJson);
        } else {
            DPRINTLN("Missing duration parameter");
            request->send(400, json, F("\"Missing val parameter in query (true|false)\""));
        }
    });

    server.on(PSTR("/ping"), HTTP_GET, [json, trueJson, falseJson, system](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/ping"));
        system->shouldPingPixelServer();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/ram"), HTTP_GET, [json](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/ram"));
        request->send(200, json, String(ESP.getFreeHeap()));
    });

    server.on(PSTR("/uptime"), HTTP_GET, [json](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/uptime"));
        request->send(200, json, String(NTP.getUptime()));
    });

    server.on(PSTR("/notify/dong"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/dong\t"));
        bool result = system->dong();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/notify/song"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/song\t"));
        bool result = system->notify();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/notify/alert"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/notify/alert\t"));
        bool result = system->alert();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/message/date"), HTTP_GET, [system, json, trueJson](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/message/date\t"));
        system->showDateMessage();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/intensity"), HTTP_GET, [valArg, system, json, trueJson](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]/intensity\t"));
        if (request->hasArg(valArg)) {
            byte val = (byte) request->arg(valArg).toInt();
            DPRINT(F("Val: ")); DPRINTLN(val);
            system->setMatrixIntensity(val);
            request->send(201, json, trueJson);
        } else {
            DPRINTLN("Missing val parameter");
            request->send(400, json, F("\"Missing val parameter in query\""));
        }
    });

    server.onNotFound([json](AsyncWebServerRequest *request) {
        DPRINTLN(F("[WEB SERVER]Not found\t"));
        request->send(404, json, F("\"Not found\""));
    });
}

void WebServer::begin() {
    DPRINTLN(F("[WEB SERVER]Start"));
    LittleFS.begin();
    AsyncElegantOTA.begin(&server);
    server.begin();
}
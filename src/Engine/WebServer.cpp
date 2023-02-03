#include <LittleFS.h>
#include "Applets/AppletCountdown.h"
#include "WebServer.h"
#include "Applets/AppletMessage.h"
#include "Applets/AppletStaticSymbols.h"

WebServer::WebServer(System* system) : server(AsyncWebServer(80)) {
    const String& json = F("application/json");
    const String& trueStr = F("true");
    const String& trueJson = F("\"true\"");
    const String& falseJson = F("\"false\"");
    const String& impossibleToGetApplet = F("\"Impossible to get applet\"");
    const __FlashStringHelper* durationArg = F("duration");
    const __FlashStringHelper* restartArg = F("restart");
    const __FlashStringHelper* valArg = F("val");
    const __FlashStringHelper* msgArg = F("msg");

    server.on(PSTR("/"), HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, F("/index.html"));
    });

    server.on(PSTR("/message/add"), HTTP_GET, [msgArg, restartArg, json, trueJson, falseJson, system, durationArg, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletMessage* applet = (AppletMessage*) orchestror->getAppletByType(MESSAGE);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        if (request->hasArg(msgArg) && request->arg(msgArg).length() > 0) {
            String msg = request->arg(msgArg);

            unsigned long duration = 0;
            if (request->hasArg(durationArg)) {
                duration = (unsigned long) request->arg(durationArg).toInt();
            }

            if (applet->addMessage(msg.c_str(), duration)) {
                request->send(201, json, trueJson);
            } else {
                request->send(500, json, F("\"Impossible to get applet or message queue full\""));
            }
        } else {
            request->send(400, json, F("\"Missing msg parameter in query\""));
        }
    });

    server.on(PSTR("/message/loop/stop"), HTTP_GET, [system, json, trueJson, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletMessage* applet = (AppletMessage*) orchestror->getAppletByType(MESSAGE);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        applet->stopTimer();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/symbols/set"), HTTP_GET, [msgArg, restartArg, json, trueJson, falseJson, system, durationArg, impossibleToGetApplet](AsyncWebServerRequest *request) {
        if (request->hasArg(msgArg) && request->arg(msgArg).length() > 0 && request->hasArg(durationArg)) {
            AppletStaticSymbols* applet = (AppletStaticSymbols*) system->getAppletByTypeOnAnyOrchestor(STATIC_SYMBOLS);
            if (applet == nullptr) {
                request->send(500, json, impossibleToGetApplet);
                return;
            }

            if (applet->addSymbols(request->arg(msgArg).c_str(), (unsigned long) request->arg(durationArg).toInt())) {
                request->send(201, json, trueJson);
            } else {
                request->send(500, json, F("\"Impossible to get applet or message queue full\""));
            }
        } else {
            request->send(400, json, F("\"Missing msg parameter or duration in query\""));
        }
    });

    server.on(PSTR("/countdown/start"), HTTP_GET, [msgArg, restartArg, json, trueJson, system, durationArg, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletCountdown* applet = (AppletCountdown*) orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        if (applet->currentlyRunning() && !request->hasArg(restartArg)) {
            request->send(403, json, F("\"There is already a countdown. Stop it before add a new one\""));
            return;
        }

        if (request->hasArg(durationArg)) {
            applet->startTimer((unsigned long) request->arg(durationArg).toInt(), request->arg(msgArg).c_str());
            request->send(201, json, trueJson);
        } else {
            request->send(400, json, F("\"Missing duration(sec) or msg(optional) parameter in query\""));
        }
    });

    server.on(PSTR("/countdown/pause"), HTTP_GET, [system, json, trueJson, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletCountdown* applet = (AppletCountdown*) orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        applet->timer.pause();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/countdown/resume"), HTTP_GET, [system, json, trueJson, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletCountdown* applet = (AppletCountdown*) orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        applet->timer.resume();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/countdown/stop"), HTTP_GET, [system, json, trueJson, impossibleToGetApplet](AsyncWebServerRequest *request) {
        Orchestror* orchestror = system->getMainOrchestor();
        AppletCountdown* applet = (AppletCountdown*) orchestror->getAppletByType(COUNTDOWN);
        if (applet == nullptr) {
            request->send(500, json, impossibleToGetApplet);
            return;
        }

        applet->stopTimer(false);
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/state"), HTTP_GET, [valArg, system, json, trueJson, trueStr](AsyncWebServerRequest *request) {
        if (request->hasArg(valArg)) {
            bool state = request->arg(valArg).equalsIgnoreCase(trueStr);
            system->setMatrixActivated(state);
            request->send(200, json, trueJson);
        } else {
            request->send(400, json, F("\"Missing val parameter in query (true|false)\""));
        }
    });

    server.on(PSTR("/ping"), HTTP_GET, [json, trueJson, falseJson, system](AsyncWebServerRequest *request) {
        system->shouldPingPixelServer();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/ram"), HTTP_GET, [json, this](AsyncWebServerRequest *request) {
        sprintf_P(this->tempString, PSTR("%lu"), ESP.getFreeHeap());
        request->send(200, json, this->tempString);
    });

    server.on(PSTR("/uptime"), HTTP_GET, [json, this](AsyncWebServerRequest *request) {
        sprintf_P(this->tempString, PSTR("%lu"), NTP.getUptime());
        request->send(200, json, this->tempString);
    });

    server.on(PSTR("/version"), HTTP_GET, [json, this](AsyncWebServerRequest *request) {
        sprintf_P(this->tempString, PSTR("%.2f"), VERSION);
        request->send(200, json, this->tempString);
    });

    server.on(PSTR("/notify/dong"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        bool result = system->dong();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/notify/song"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        bool result = system->notify();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/notify/alert"), HTTP_GET, [system, json, trueJson, falseJson](AsyncWebServerRequest *request) {
        bool result = system->alert();
        request->send(result ? 200 : 500, json, result ? trueJson : falseJson);
    });

    server.on(PSTR("/message/date"), HTTP_GET, [system, json, trueJson](AsyncWebServerRequest *request) {
        system->showDateMessage();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/reboot"), HTTP_GET, [system, json, trueJson](AsyncWebServerRequest *request) {
        ESP.restart();
        request->send(200, json, trueJson);
    });

    server.on(PSTR("/intensity"), HTTP_GET, [valArg, system, json, trueJson](AsyncWebServerRequest *request) {
        if (request->hasArg(valArg)) {
            byte val = (byte) request->arg(valArg).toInt();
            system->setMatrixIntensity(val);
            request->send(201, json, trueJson);
        } else {
            request->send(400, json, F("\"Missing val parameter in query\""));
        }
    });

    server.onNotFound([json](AsyncWebServerRequest *request) {
        request->send(404, json, F("\"Not found\""));
    });
}

void WebServer::begin() {
    LittleFS.begin();
    AsyncElegantOTA.begin(&server);
    server.begin();
}
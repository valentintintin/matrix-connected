#include <Slides/SlideMessage.h>
#include "WebServer.h"

WebServer::WebServer(Screen *screen) : server(AsyncWebServer(80)) {
    server.on("/add_message", HTTP_GET, [screen](AsyncWebServerRequest *request) {
        if (request->hasParam("msg")) {
            screen->addSlide(new SlideMessage(screen, request->getParam("msg")->value()));
            request->send(201, PSTR("text/plain"), PSTR("OK"));
        } else {
            request->send(400, PSTR("text/plain"), PSTR("Missing msg parameter in query"));
        }
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, PSTR("text/plain"), PSTR("Not found"));
    });
}

WebServer::~WebServer() {
}

void WebServer::begin() {
    server.begin();
}
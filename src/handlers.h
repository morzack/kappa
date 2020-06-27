#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <WebServer.h>

void handleRoot(WebServer &server) {
    server.send(200, "text/html", "kappa");
}

#endif
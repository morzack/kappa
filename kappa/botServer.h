#ifndef BOT_SERVER_H_
#define BOT_SERVER_H_

#include "robot.h"
#include <WebServer.h>
#include <ArduinoJson.h>

struct BotServer
{
public:
    BotServer(Robot *robot, WebServer *server);

    void registerHandlers();

    /*** GENERIC HANDLERS ***/
    void pingHandlerGET();

    /*** ROBOT HANDLERS ***/
    void commandPOST();

private:
    Robot *robot;
    WebServer *server;

    bool extractBody(StaticJsonDocument<250> &json);
};

#endif
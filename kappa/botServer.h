#ifndef BOT_SERVER_H_
#define BOT_SERVER_H_

#include "robot.h"
#include <WebServer.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>

struct BotServer
{
public:
    BotServer(Robot *robot, WebServer *server, websockets::WebsocketsServer *socketServer);

    void registerHandlers();

    /*** GENERIC HANDLERS ***/
    void pingHandlerGET();

    /*** ROBOT HANDLERS ***/
    void commandPOST();

    /*** WEBSOCKET HANDLER ***/
    void initClient(websockets::WebsocketsClient *client);
    bool loopClient(websockets::WebsocketsClient *client);
    void endClient(websockets::WebsocketsClient *client);

    String getTelemetry();

    void handleNewClient(websockets::WebsocketsClient *client);
    void socketLoop();

private:
    Robot *robot;
    WebServer *server;
    websockets::WebsocketsServer *socketServer;

    bool extractBody(StaticJsonDocument<250> &json);
};

#endif

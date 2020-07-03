#ifndef BOT_SERVER_H_
#define BOT_SERVER_H_

#include "robot.h"
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>

struct BotServer
{
public:
    BotServer(Robot *robot, websockets::WebsocketsServer *socketServer);

    void HandleNewClient(websockets::WebsocketsClient *client);

    /** WEBSOCKET HANDLERS **/
    void InitClient(websockets::WebsocketsClient *client);
    bool LoopClient(websockets::WebsocketsClient *client);
    void EndClient(websockets::WebsocketsClient *client);
    void SocketLoop();
    
    String GenTelemetry();
    
    /** PARSE INBOUND **/
    bool HandleCommandString(String command);

private:
    Robot *robot;
    websockets::WebsocketsServer *socketServer;
};

#endif

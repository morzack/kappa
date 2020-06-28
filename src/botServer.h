#ifndef BOT_SERVER_H_
#define BOT_SERVER_H_

#include "robot.h"
#include <WebServer.h>

struct BotServer
{
public:
    BotServer(Robot *robot, WebServer *server);
    
    void registerHandlers();

    /*** GENERIC HANDLERS ***/
    void pingHandlerGET();

    /*** ROBOT HANDLERS ***/
    void setShooterPowerPOST();
    void setTurretStatePOST();
    void drivePOST();

private:
    Robot *robot;
    WebServer *server;
};

#endif
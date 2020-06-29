#include "botServer.h"

BotServer::BotServer(Robot *robot, WebServer *server) : robot(robot), server(server) {}

void BotServer::registerHandlers()
{
    server->on("/ping", HTTP_GET, [this]() { pingHandlerGET(); });

    server->on("/command", HTTP_POST, [this]() { commandPOST(); });
}

/*** GENERIC HANDLERS ***/
void BotServer::pingHandlerGET()
{
    server->send(200, "text/html", "kappa");
}

/*** ROBOT HANDLERS ***/
void BotServer::commandPOST()
{
    StaticJsonDocument<250> json;
    if (!extractBody(json))
    {
        return;
    }
    if (!(json.containsKey("leftPower") &&
          json.containsKey("rightPower") &&
          json.containsKey("shootPower") &&
          json.containsKey("turretMode")))
    {
        server->send(400, "text/html", "JSON keys missing");
        return;
    }

    String turretStateStr = json["turretMode"];
    if (turretStateStr == "stop")
    {
        robot->moveTurret(TurretState::STOP);
    }
    else if (turretStateStr == "clockwise")
    {
        robot->moveTurret(TurretState::CLOCKWISE);
    }
    else if (turretStateStr == "counterclockwise")
    {
        robot->moveTurret(TurretState::COUNTERCLOCKWISE);
    }
    else
    {
        robot->moveTurret(TurretState::STOP);
    }

    robot->tankDrive(json["leftPower"], json["rightPower"]);
    robot->shootTurret(json["shootPower"]);

    server->send(200, "text/html", "ok");
}

/*** UTIL ***/
bool BotServer::extractBody(StaticJsonDocument<250> &json)
{
    if (!server->hasArg("plain"))
    {
        server->send(400, "text/html", "JSON body missing");
        return false;
    }
    String body = server->arg("plain");
    deserializeJson(json, body);
    return true;
}
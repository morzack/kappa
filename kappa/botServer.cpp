#include "botServer.h"
#include <ArduinoJson.h>

BotServer::BotServer(Robot *robot, WebServer *server) : robot(robot), server(server) {}

void BotServer::registerHandlers()
{
    server->on("/ping", HTTP_GET, [this]() { pingHandlerGET(); });

    server->on("/setShooterPower", HTTP_POST, [this]() { setShooterPowerPOST(); });
    server->on("/setTurretState", HTTP_POST, [this]() { setTurretStatePOST(); });
    server->on("/drive", HTTP_POST, [this]() { drivePOST(); });
}

/*** GENERIC HANDLERS ***/
void BotServer::pingHandlerGET()
{
    server->send(200, "text/html", "kappa");
}

/*** ROBOT HANDLERS ***/
void BotServer::setShooterPowerPOST()
{
    // if (!server->hasArg("plain"))
    // {
    //     server->send(400, "text/html", "JSON body missing");
    //     return;
    // }
    // String body = server->arg("plain");
    // StaticJsonDocument<250> jdoc;
    // deserializeJson(jdoc, body);
    // if (!jdoc.containsKey("power"))
    // {
    //     server->send(400, "text/html", "JSON key 'power' missing");
    //     return;
    // }

    // robot->shootTurret(jdoc["power"]);
    server->send(200, "text/html", "ok");
}

void BotServer::setTurretStatePOST()
{
    // if (!server->hasArg("plain"))
    // {
    //     server->send(400, "text/html", "JSON body missing");
    //     return;
    // }
    // String body = server->arg("plain");
    // StaticJsonDocument<250> jdoc;
    // deserializeJson(jdoc, body);
    // if (!jdoc.containsKey("state"))
    // {
    //     server->send(400, "text/html", "JSON key 'state' missing");
    //     return;
    // }

    // String stateStr = jdoc["state"];
    // if (stateStr == "stop")
    // {
    //     robot->moveTurret(TurretState::STOP);
    // }
    // else if (stateStr == "clockwise")
    // {
    //     robot->moveTurret(TurretState::CLOCKWISE);
    // }
    // else if (stateStr == "counterclockwise")
    // {
    //     robot->moveTurret(TurretState::COUNTERCLOCKWISE);
    // }
    // else
    // {
    //     robot->moveTurret(TurretState::STOP);
    // }
    server->send(200, "text/html", "ok");
}

void BotServer::drivePOST()
{
    // if (!server->hasArg("plain"))
    // {
    //     server->send(400, "text/html", "JSON body missing");
    //     return;
    // }
    // String body = server->arg("plain");
    // StaticJsonDocument<250> jdoc;
    // deserializeJson(jdoc, body);
    // if (!jdoc.containsKey("left") || !jdoc.containsKey("right"))
    // {
    //     server->send(400, "text/html", "JSON key 'left' or 'right' missing");
    //     return;
    // }

    // robot->tankDrive(jdoc["left"], jdoc["right"]);
    server->send(200, "text/html", "ok");
}
#include "botServer.h"

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
    String powerStr = server->arg("power");
    robot->shootTurret(powerStr.toFloat());
    server->send(200, "text/html", "ok");
}

void BotServer::setTurretStatePOST()
{
    String stateStr = server->arg("state");
    if (stateStr == "stop")
    {
        robot->moveTurret(TurretState::STOP);
    }
    else if (stateStr == "clockwise")
    {
        robot->moveTurret(TurretState::CLOCKWISE);
    }
    else if (stateStr == "counterclockwise")
    {
        robot->moveTurret(TurretState::COUNTERCLOCKWISE);
    }
    else
    {
        robot->moveTurret(TurretState::STOP);
    }
    server->send(200, "text/html", "ok");
}

void BotServer::drivePOST()
{
    String leftPowerStr = server->arg("left");
    String rightPowerStr = server->arg("right");
    robot->tankDrive(leftPowerStr.toFloat(), rightPowerStr.toFloat());
    server->send(200, "text/html", "ok");
}
#include <Arduino.h>

#include <Alfredo_NoU2.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoWebsockets.h>

#include "robot.h"
#include "botServer.h"

Robot* robot;
BotServer* botServer;

void setup() {
    websockets::WebsocketsServer websocketServer;

    NoU_Motor shooterMotor(1);
    Shooter shooter(&shooterMotor);

    NoU_Motor turretMotor(2);
    Turret turret(&turretMotor);

    NoU_Motor leftMotors(3);
    NoU_Motor rightMotors(4);
    NoU_Drivetrain drivetrain(&leftMotors, &rightMotors);

    robot = new Robot(&shooter, &turret, &drivetrain);
    botServer = new BotServer(robot, &websocketServer);

    RSL::initialize();

    WiFi.softAP("kappanet");

    websocketServer.listen(8080);
}

void loop() {
    botServer->SocketLoop();
    robot->Execute();

    // RSL logic
    // if (millis() - lastTimePacketReceived > 1000)
    // {
    //     RSL::setState(RSL_DISABLED);
    // }
    // else
    // {
    //     RSL::setState(RSL_ENABLED);
    // }
    // RSL::update();
}

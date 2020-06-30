#include <Arduino.h>

#include <Alfredo_NoU2.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoWebsockets.h>

#include "robot.h"
#include "botServer.h"

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

websockets::WebsocketsServer websocketServer;

NoU_Motor shooterMotor(1);
Shooter shooter(&shooterMotor);

NoU_Motor turretMotor(2);
Turret turret(&turretMotor);

NoU_Motor leftMotors(3);
NoU_Motor rightMotors(4);
NoU_Drivetrain drivetrain(&leftMotors, &rightMotors);

Robot robot(&shooter, &turret, &drivetrain);

BotServer botServer(&robot, &server, &websocketServer);

void setup()
{
    RSL::initialize();

    WiFi.softAP("kappanet");

    botServer.registerHandlers();

    websocketServer.listen(8080);
    server.begin();
}

void loop()
{
    server.handleClient();
    botServer.socketLoop();

    robot.execute();

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

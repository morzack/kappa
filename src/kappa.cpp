#include <Arduino.h>

#include <Alfredo_NoU2.h>
#include <WiFi.h>
#include <WebServer.h>

#include "robot.h"
#include "botServer.h"

const char *ssid = "kappanet";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

NoU_Motor shooterMotor(0);
Shooter shooter(&shooterMotor);

NoU_Motor turretMotor(1);
Turret turret(&turretMotor);

NoU_Motor leftMotors(3);
NoU_Motor rightMotors(4);
NoU_Drivetrain drivetrain(&leftMotors, &rightMotors);

Robot robot(&shooter, &turret, &drivetrain);

BotServer botServer(&robot, &server);

void setup()
{
    Serial.begin(9600);
    RSL::initialize();

    WiFi.enableAP(true);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid);

    botServer.registerHandlers();

    /*** Webpage Serving ***/

    server.begin();
}

void loop()
{
    server.handleClient();

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

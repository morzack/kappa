#include <Arduino.h>

#include <Alfredo_NoU2.h>
#include <WiFi.h>
#include <WebServer.h>

#include "handlers.h"

const char *ssid = "KappaAP";

IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

void setup()
{
    Serial.begin(9600);
    RSL::initialize();

    WiFi.enableAP(true);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    WiFi.softAP(ssid);

    server.on("/", []() { handleRoot(server); });
    server.begin();
}

void loop()
{
    server.handleClient();

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

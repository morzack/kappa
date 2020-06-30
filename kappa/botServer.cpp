#include "botServer.h"

BotServer::BotServer(Robot *robot, WebServer *server, websockets::WebsocketsServer *socketServer) : robot(robot), server(server), socketServer(socketServer) {}

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

/*** WEBSOCKETS ***/
void BotServer::initClient(websockets::WebsocketsClient *client) {
    client->send("ACK: kappanet connected, peko");
}

bool BotServer::loopClient(websockets::WebsocketsClient *client) {
    // return true/false based on disconnect
    websockets::WebsocketsMessage message = client->readBlocking();
    switch (message.type()) {
        case websockets::MessageType::Empty:
            break;
        case websockets::MessageType::Text:
            break;
        case websockets::MessageType::Binary:
            break;
        case websockets::MessageType::Ping:
            break;
        case websockets::MessageType::Pong:
            break;
        case websockets::MessageType::Close:
            return false;
        default:
            // lol idk we'll just peko whatever
            break;
    }
    String data = getTelemetry();
    client->send(data != "" ? data + ", peko" : "peko");
    return true;
}

void BotServer::endClient(websockets::WebsocketsClient *client) {
    client->send("END: kappanet disconnect, peko");
}

String BotServer::getTelemetry() {
    return "";
}

void BotServer::handleNewClient(websockets::WebsocketsClient *client) {
    initClient(client);
    bool looping = true;
    while (looping) {
        looping = loopClient(client);
    }
    endClient(client);
}

void BotServer::socketLoop() {
    websockets::WebsocketsClient client = socketServer->accept();
    if (client.available()) {
        handleNewClient(&client);
    }
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

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
    if (!server->hasArg("plain"))
    {
        server->send(400, "text/html", "JSON body missing");
        return;
    }
    String body = server->arg("plain");
    if (handleCommandString(body)) {
        server->send(200, "text/html", "ok");
        return;
    }
    server->send(400, "text/html", "malformed command");
}

bool BotServer::handleCommandString(String command) {
    if (command == "") {
        return false;
    }

    StaticJsonDocument<250> json;
    DeserializationError err;
    err = deserializeJson(json, command.substring(0, command.length()-5));
    if (err != DeserializationError::Ok) {
        return false;
    }

    if (!(json.containsKey("leftPower") &&
                json.containsKey("rightPower") &&
                json.containsKey("shootPower") &&
                json.containsKey("turretMode")))
    {
        return false;
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

    return true;
}

/*** WEBSOCKETS ***/
void BotServer::initClient(websockets::WebsocketsClient *client) {
    client->send("ACK: kappanet connected");
}

bool BotServer::loopClient(websockets::WebsocketsClient *client) {
    // return true/false based on disconnect
    websockets::WebsocketsMessage message = client->readBlocking();
    switch (message.type()) {
        // for most of these messages we can just ignore them
        // really the only thing that we care about is the "Text" type
        case websockets::MessageType::Empty:
            break;
        case websockets::MessageType::Text:
            handleCommandString(message.data());
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
            break;
    }
    String telemetryData = getTelemetry();
    client->send(telemetryData);
    return true;
}

void BotServer::endClient(websockets::WebsocketsClient *client) {
    client->send("END: kappanet disconnect");
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


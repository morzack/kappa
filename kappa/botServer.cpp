#include "botServer.h"

BotServer::BotServer(Robot *robot, websockets::WebsocketsServer *socketServer)
        : robot(robot),
          socketServer(socketServer) {}

void BotServer::HandleNewClient(websockets::WebsocketsClient *client) {
    InitClient(client);
    bool looping = true;
    while (looping) {
        looping = LoopClient(client);
    }
    EndClient(client);
}

/*** WEBSOCKET HANDLERS ***/
void BotServer::InitClient(websockets::WebsocketsClient *client) {
    client->send("kappanet connected");
}

bool BotServer::LoopClient(websockets::WebsocketsClient *client) {
    // return true/false based on disconnect
    websockets::WebsocketsMessage message = client->readBlocking();
    bool sendTelemetry = true;
    switch (message.type()) {
        case websockets::MessageType::Text:
            if (!HandleCommandString(message.data())) {
                sendTelemetry = false;
            }
            break;
        case websockets::MessageType::Close:
            return false;
        default:
            break;
    }
    if (sendTelemetry) {
        client->send(GenTelemetry());
    } else {
        client->send("malformed packet or parsing error");
    }
    return true;
}

void BotServer::EndClient(websockets::WebsocketsClient *client) {
    client->send("kappanet disconnected");
}

void BotServer::SocketLoop() {
    websockets::WebsocketsClient client = socketServer->accept();
    if (client.available()) {
        HandleNewClient(&client);
    }
}

String BotServer::GenTelemetry() {
    return "";
}

bool BotServer::HandleCommandString(String command) {
    if (command == "") {
        return false;
    }

    StaticJsonDocument<250> json;
    DeserializationError err;
    err = deserializeJson(json, command.substring(0, command.length()-5));
    if (err != DeserializationError::Ok) {
        return false;
    }

    if (!(  json.containsKey("leftPower") &&
            json.containsKey("rightPower") &&
            json.containsKey("shootPower") &&
            json.containsKey("turretMode"))) {
        return false;
    }

    String turretStateStr = json["turretMode"];
    if (turretStateStr == "stop") {
        robot->MoveTurret(TurretState::STOP);
    } else if (turretStateStr == "clockwise") {
        robot->MoveTurret(TurretState::CLOCKWISE);
    } else if (turretStateStr == "counterclockwise") {
        robot->MoveTurret(TurretState::COUNTERCLOCKWISE);
    } else {
        robot->MoveTurret(TurretState::STOP);
    }

    robot->TankDrive(json["leftPower"], json["rightPower"]);
    robot->ShootTurret(json["shootPower"]);

    return true;
}


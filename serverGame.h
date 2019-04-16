// serverGame.h
// Simeon Ng
// Header for ServerGame class.

#ifndef BATTLESHIP_SERVERGAME_H
#define BATTLESHIP_SERVERGAME_H

#include <memory>
#include "server.h"
#include "networkData.h"

// Class : ServerGame
// Handles server side information for Battleship Game.

class ServerGame {
public:
    ServerGame();
    ~ServerGame() = default;
    void update();
    void receiveFromClient();

    void sendActionPackets();
    void sendPrompt();

private:
    static unsigned int _clientID;      // ID's for client when they connect.
    std::unique_ptr<Server> _network;   // Server object that handles connections.
    char _networkData[MAX_PACKET_SIZE]; // Data buffer for receivingFromClient()

};


#endif //BATTLESHIP_SERVERGAME_H

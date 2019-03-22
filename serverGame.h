// serverGame.h
// Simeon Ng
// Updated 3/22/19
// Header for ServerGame class.

#ifndef BATTLESHIP_SERVERGAME_H
#define BATTLESHIP_SERVERGAME_H

#include <memory>
#include "server.h"

// Class : ServerGame
// Handles server side information for Battleship Game.

class ServerGame {
public:
    ServerGame();
    ~ServerGame() = default;
    void update();

private:
    static unsigned int _clientID;      // ID's for client when they connect.
    std::unique_ptr<Server> _network;   // Server object that handles connections.

};


#endif //BATTLESHIP_SERVERGAME_H

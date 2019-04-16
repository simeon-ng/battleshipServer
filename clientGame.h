// clientGame.h
// Simeon Ng
// Header for ClientGame class.

#ifndef BATTLESHIP_CLIENTGAME_H
#define BATTLESHIP_CLIENTGAME_H

#include <winsock2.h>
#include <windows.h>
#include "client.h"
#include "networkData.h"
#include <memory>

// Class : ClientGame
// Handles the client side information for the Battleship game.

class ClientGame {
public:
    ClientGame();
    ~ClientGame() = default;
    void sendActionPackets();
    void update();

private:
    std::unique_ptr<Client> _network;    // Client object that handles connections.
    char _networkData[MAX_PACKET_SIZE];  // Buffer

};


#endif //BATTLESHIP_CLIENTGAME_H

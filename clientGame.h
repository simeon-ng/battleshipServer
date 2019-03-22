// clientGame.h
// Simeon Ng
// Updated 3/22/19
// Header for ClientGame class.

#ifndef BATTLESHIP_CLIENTGAME_H
#define BATTLESHIP_CLIENTGAME_H

#include <winsock2.h>
#include <windows.h>
#include "client.h"
#include <memory>

// Class : ClientGame
// Handles the client side information for the Battleship game.

class ClientGame {
public:
    ClientGame();
    ~ClientGame() = default;

private:
    std::unique_ptr<Client> _network;    // Client object that handles connections.

};


#endif //BATTLESHIP_CLIENTGAME_H

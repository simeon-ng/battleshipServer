// serverGame.cpp
// Simeon Ng
// Updated 3/22/19

#include "serverGame.h"

unsigned int ServerGame::_clientID;
ServerGame::ServerGame() {
    _clientID = 0;
    _network = std::make_unique<Server>();
}

void ServerGame::update() {
    if (_network->acceptClient(_clientID)) {
        printf("Client %d has connected to the server.\n", _clientID);
        _clientID++;
    }
}
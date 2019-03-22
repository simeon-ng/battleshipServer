// serverGame.h
// Simeon Ng
// Updated 3/22/19

#ifndef BATTLESHIP_SERVERGAME_H
#define BATTLESHIP_SERVERGAME_H

#include <memory>
#include "server.h"

// Class : ServerGame

class ServerGame {
public:
    ServerGame();
    ~ServerGame() = default;
    void update();

private:
    static unsigned int _clientID;
    std::unique_ptr<Server> _network;

};


#endif //BATTLESHIP_SERVERGAME_H

// clientGame.cpp
// Simeon Ng
// Updated 3/22/19
// Source file for ClientGame class.

#include "clientGame.h"

ClientGame::ClientGame() {
    _network = std::make_unique<Client>();
}
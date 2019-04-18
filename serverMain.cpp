// serverMain.cpp
// Server main function for Battleship game.

#include "game.h"
#include "clientGame.h"
#include "serverGame.h"
#include <memory>

int main() {
    std::unique_ptr<ServerGame> server = std::make_unique<ServerGame>();
    while(true) {
        cout << "again" << endl;
        server->update();
    }
}
// clientMain.cpp
// Client main function for Battleship game.

#include "game.h"
#include "clientGame.h"
#include "serverGame.h"
#include <memory>

int main() {
    std::unique_ptr<ClientGame> client = std::make_unique<ClientGame>();
    while(true) {
        system("PAUSE");
        cout << "again" << endl;
        client->update();
    }
}


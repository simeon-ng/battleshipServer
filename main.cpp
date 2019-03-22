// main.cpp
// Simeon Ng
// Jason Herning
// Updated: 3/22/19
// Game Class Source File

#include "game.h"
#include "clientGame.h"
#include "serverGame.h"
#include <memory>
#include <process.h>

// Temporary Global functions for server/client
void serverLoop(void*);
void clientLoop();

std::unique_ptr<ServerGame> server;
std::unique_ptr<ClientGame> client;

// main()
int main() {
    // Testing server/client

    // Initialize server.
    server = std::make_unique<ServerGame>();
    // Create separate thread for server so it can keep checking for new clients.
    _beginthread(serverLoop, 0, (void*) 12);
    // Initialize client.
    client = std::make_unique<ClientGame>();

    clientLoop();

    // Game Loop
    Game g;
    g.fancyPrint("WELCOME TO BATTLESHIP");
    while(true) {
        string input;
        cout << "[P]lay or [Q]uit" << endl;
        getline(cin, input);
        if(!cin) {
            cout << "Input error. Try again." << endl;
            continue;
        }
        switch(input[0]) {
            case 'P' : g.gameLoop(); break;
            case 'p' : g.gameLoop(); break;
            case 'Q' : cout << "Goodbye!" << endl; return 0;
            case 'q' : cout << "Goodbye!" << endl; return 0;
            default  : cout << "Not a valid input. Try again" << endl; continue;
        }
    }
}

void serverLoop(void*) {
    while(true) {
        server->update();
    }
}

void clientLoop() {
    while(true) {
        // client->update()
    }
}
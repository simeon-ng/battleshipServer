// main.cpp
// Simeon Ng
// Updated: 4/15/19
// Game Class Source File

#include "game.h"
#include "clientGame.h"
#include "serverGame.h"
#include <memory>
#include <process.h>
#include <thread>

// Temporary Global functions for server/client
void serverLoop(void*);
void clientLoop();

std::unique_ptr<ServerGame> server;
std::unique_ptr<ClientGame> client;

void serverLoop(void*) {
    server = std::make_unique<ServerGame>();
    while(true) {
        server->update();
    }
}

void clientLoop() {
    // Game Loop
    Game g;
    g.fancyPrint("WELCOME TO BATTLESHIP");
    while(true) {
        string input;
        cout << "[P]lay or [Q]uit. [C]onnect to server." << endl;
        getline(cin, input);
        if(!cin) {
            cout << "Input error. Try again." << endl;
            continue;
        }
        switch(input[0]) {
            case 'P' : g.gameLoop(); break;
            case 'p' : g.gameLoop(); break;
            case 'Q' : cout << "Goodbye!" << endl; return;
            case 'q' : cout << "Goodbye!" << endl; return;
            case 'C' :
                // Initialize client.
                client = std::make_unique<ClientGame>();
                while(true) {
                    client->update();
                }
            default  : cout << "Not a valid input. Try again" << endl; continue;
        }
    }

}

// main()
int main() {
    // Testing server/client

    // Initialize server.
    // Create separate thread for server so it can keep checking for new clients.
    _beginthread(serverLoop, 0, (void*)12);

    clientLoop();
}
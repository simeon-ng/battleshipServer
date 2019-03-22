// main.cpp
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Game Class Source File

#include "game.h"
#include "client.h"
#include "server.h"

int main() {
    Client c;
    Server s;
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
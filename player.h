// player.h
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Player Class Source File

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "board.h"

// ---- Class Player ----

class Player {

    // ---- Player: Ctor ----

public:
    Player();

    // ---- Player: Public Member Functions ----

public:
    size_t getLength() const;
    size_t getWidth() const;
    bool getAllSunk();
    bool isCoordTakenShip(const Coords &);
    bool isCoordTakenFired(const Coords &);
    bool isCoordTakenHits(const Coords &);

    void addShip(const Ship &);
    bool hit(const Coords &);
    Board getBoard()const;


    // ---- Player: Data Members ----

private:
    Board _shipBoard;   // Default 10x10 board. Tracks ships, hits and misses.
};


#endif //BATTLESHIP_PLAYER_H

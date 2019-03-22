// board.h
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Board Class Header File

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include "ship.h"
using std::ostream;
using std::vector;
using std::find_if;

// ---- Class Board ----

class Board {

    // ---- Board: Ctors ----

public:
    Board();
    explicit Board(size_t);
    Board(size_t, size_t);


    // ---- Board: Public Member Functions ----

public:
    size_t getLength() const;
    size_t getWidth() const;
    vector<Ship> getShips() const;
    vector<Coords> getCoordsFiredAt() const;
    vector<Coords> getCoordsHit() const;

    size_t size() const;
    void addShip(const Ship &);
    void addCoordHorizontal(const Ship &);
    void addCoordVertical(const Ship &);
    bool isCoordTakenShip(const Coords&) const;
    bool isCoordTakenFiredAt(const Coords & c) const;
    bool isCoordTakenHit(const Coords & c) const;
    bool attack(const Coords &);
    void attackShip(const Coords &);
    bool isSunk(const Ship &);
    bool allSunk();

    // ---- Board: Data Members ----

private:
    size_t _length = 0;              // Length of board. Corresponds to X coordinate.
    size_t _width = 0;               // Width of board. Corresponds to Y coordinate.
    vector<Ship> _ships;             // List of ships added to the board
    vector<Coords> _shipCoords;      // List of Coords that are taken by ships
    vector<Coords> _coordsFiredAt;   // List of Coords that have been fired at. Acts as upper board.
    vector<Coords> _coordsHit;       // List of Coords that have been registered as hits.

};

#endif //BATTLESHIP_BOARD_H

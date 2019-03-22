// ship.h
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Ship Class Header File

#ifndef CS372_BATTLESHIP_SHIP_H
#define CS372_BATTLESHIP_SHIP_H

#include <iostream>
#include <cstddef>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

// ---- Struct Coords ----

// Coordinate system for ships to be placed on.
struct Coords {
    size_t x;
    size_t y;

    // 2-param Ctor
    Coords(size_t x, size_t y) : x(x), y(y) {}

    // Operator=
    Coords& operator=(const Coords& c) {
        x = c.x, y = c.y;
        return *this;
    }

    // Operator==
    bool operator==(const Coords& c) const {
        return x == c.x && y == c.y;
    }

    // Operator!=
    bool operator!=(const Coords& c) const {
        return !(*this == c);
    }
};

// ---- Class Ship ----

//size will always be from size 1-5
//position will always be from 1-100
class Ship {

    // ---- Ship: Ctor ----

public:
    Ship(Coords c1, Coords c2);

    // ---- Ship: Public Member Functions ----

public:
    size_t getLength();
    Coords getBegin() const;
    Coords getEnd() const;
    bool getOrientation() const;
    bool attack(const Coords & c);
    bool isSunk();

public:
    bool operator==(const Ship &) const;

    // ---- Ship: Data Members ----

private:
    const Coords _begin;    // Coords of Beginning of ship
    const Coords _end;      // Coords of End of ship
    bool _orientation;      // Orientation of ship;
                            // True == Horizontal, False == Vertical
    vector<bool> _hits;
    bool _sunk = false;     // True == sunk, False == still floating

};


#endif //CS372_BATTLESHIP_SHIP_H

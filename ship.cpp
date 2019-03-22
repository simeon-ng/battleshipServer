// ship.cpp
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Ship Class Source File

#include "ship.h"

// ---- Ship: Ctor ----

// 2-Parameter ctor
Ship::Ship(Coords c1, Coords c2) :
    _begin(c1), _end(c2) {
    _hits.resize(getLength());
}

// ---- Ship: Public Member Functions ----

// getLength()
// Returns ship length
std::size_t Ship::getLength() {
    if (_end.x - _begin.x == 0) {
        _orientation = false;
        return _end.y - _begin.y + 1;
    }
    _orientation = true;
    return _end.x - _begin.x + 1;
}

// getBegin()
// Returns ships beginning coordinate.
Coords Ship::getBegin() const {
    return _begin;
}

// getEnd()
// Returns ships ending coordinate.
Coords Ship::getEnd() const {
    return _end;
}

// getOrientation()
// Returns ships orientation.
bool Ship::getOrientation() const {
    return _orientation;
}

// attack()
// Attacks the ship. If true, the position on the ship has been hit.
bool Ship::attack(const Coords & c) {
    if (c.x <= _end.x && c.y <= _end.y) {
        if (_orientation) {
            _hits[_hits.size() - _end.x + c.x - 1] = true;
            return true;
        }
        else {
            _hits[_hits.size() - _end.y + c.y - 1] = true;
            return true;
        }
    }
    return false;
}

// isSunk()
// Returns true if entire ship has been hit.
bool Ship::isSunk() {
    for (auto i : _hits) {
        if (!i)
            return _sunk;
    }
    _sunk = true;
    return _sunk;
}

// ---- Ship: Operators ----

// Operator==
bool Ship::operator==(const Ship & s) const {
    return _begin == s.getBegin() && _end == s.getEnd();
}




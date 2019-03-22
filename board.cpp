// board.cpp
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Board Class Source File

#include "board.h"

// ---- Board: Ctors ----

// Default ctor
// Default board is 10x10 in size.
Board::Board() : _length(10), _width(10) {}

// 1-Param ctor
// Creates a board that is length*length in size.
Board::Board(size_t length) : _length(length), _width(length) {}

// 2-Param ctor
// Creates a board that is length*width in size.
Board::Board(size_t length, size_t width) : _length(length), _width(width) {}

// ---- Board: General Public Member Functions ----

// getLength()
// Returns length of board.
size_t Board::getLength() const { return _length; }

// getWidth()
// Returns width of board.
size_t Board::getWidth() const { return _width; }

// getShips()
// Returns a vector of ships.
vector<Ship> Board::getShips() const { return _ships; }

// getCoordsFiredAt()
// Returns the coordinates that have been fired at.
vector<Coords> Board::getCoordsFiredAt() const { return _coordsFiredAt; }

// getCoordsHit()
// Returns the coordinates that have been hit.
vector<Coords> Board::getCoordsHit() const { return _coordsHit; }

// size()
// Returns size of board.
size_t Board::size() const {
    return _length * _width;
}

// addShip()
// Adds a ship to the board.
void Board::addShip(const Ship & ship) {
    _ships.push_back(ship);

    // If horizontal
    if(ship.getOrientation())
        addCoordHorizontal(ship);
    else
        addCoordVertical(ship);
}

// addCoordHorizontal()
// Adds a ships coordinates to the board if the orientation is horizontal.
void Board::addCoordHorizontal(const Ship & ship) {
    auto addCoord = ship.getBegin();
    _shipCoords.push_back(addCoord);

    while(addCoord != ship.getEnd()) {
        addCoord.x += 1;
        _shipCoords.push_back(addCoord);
    }
}

// addCoordVertical()
// Adds a ships coordinates to the board if the orientation is vertical.
void Board::addCoordVertical(const Ship & ship) {
    auto addCoord = ship.getBegin();
    _shipCoords.push_back(addCoord);

    while(addCoord != ship.getEnd()) {
        addCoord.y += 1;
        _shipCoords.push_back(addCoord);
    }
}

// isCoordTaken()
// Returns true if coordinate given is taken up by a ship.
bool Board::isCoordTakenShip(const Coords & c) const {
    auto pred = [c](const Coords & c2) {
        return c.x == c2.x && c.y == c2.y;
    };
    auto iter = std::find_if(_shipCoords.begin(), _shipCoords.end(), pred);
    return iter != _shipCoords.end();
}


// isCoordTakenFiredAt()
// Returns true if coordinate given is taken up by a ship.
bool Board::isCoordTakenFiredAt(const Coords & c) const {
    auto pred = [c](const Coords & c2) {
        return c.x == c2.x && c.y == c2.y;
    };
    auto iter = std::find_if(_coordsFiredAt.begin(), _coordsFiredAt.end(), pred);
    return iter != _coordsFiredAt.end();
}

// isCoordTakenHit()
// Returns true if coordinate given is taken up by a ship.
bool Board::isCoordTakenHit(const Coords & c) const {
    auto pred = [c](const Coords & c2) {
        return c.x == c2.x && c.y == c2.y;
    };
    auto iter = std::find_if(_coordsHit.begin(), _coordsHit.end(), pred);
    return iter != _coordsHit.end();
}

// attack()
// Returns true if coordinate given is hit. False otherwise.
bool Board::attack(const Coords & c) {
    if(isCoordTakenShip(c)) {
        attackShip(c);
        _coordsFiredAt.push_back(c);
        _coordsHit.push_back(c);
        return true;
    }
    _coordsFiredAt.push_back(c);
    return false;
}

// attackShip()
// Finds the original ship given a coordinate and attacks it.
void Board::attackShip(const Coords & c) {
    for(auto& i : _ships) {
        if(i.attack(c))
            break;
    }
}

// isSunk()
// Returns true if the given ship is sunk. False otherwise.
bool Board::isSunk(const Ship & ship) {
    for(auto & i : _ships) {
        if(i == ship)
            return i.isSunk();
    }
    return false;
}

// allSunk()
// Returns true if all ships have been sunk. False otherwise.
bool Board::allSunk() {
    for(auto & i : _ships) {
        if(i.isSunk())
            continue;
        else
            return false;
    }
    return true;
}
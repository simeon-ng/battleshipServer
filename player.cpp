// player.cpp
// Simeon Ng
// Jason Herning
// Updated: 2/26/19
// Player Class Source File

#include "player.h"
#include "board.h"

// ---- Player: Ctor

Player::Player() = default;

// ---- Player: Public Member Functions ----

// getLength()
// Returns length of the board.
size_t Player::getLength() const {
    return _shipBoard.getLength();
}

// getWidth()
// Returns length of the board.
size_t Player::getWidth() const {
    return _shipBoard.getWidth();
}

// getAllSunk
// Returns true if all ships are sunk.
bool Player::getAllSunk() {
    return _shipBoard.allSunk();
}


bool Player::isCoordTakenShip(const Coords& c) {
    return _shipBoard.isCoordTakenShip(c);
}

bool Player::isCoordTakenFired(const Coords & c) {
    return _shipBoard.isCoordTakenFiredAt(c);
}

bool Player::isCoordTakenHits(const Coords & c) {
    return _shipBoard.isCoordTakenHit(c);
}

// addShip()
// Adds a given ship to the board.
void Player::addShip(const Ship & ship) {
    _shipBoard.addShip(ship);
}

// hit()
// Returns true if attack hit a ship. False otherwise.
bool Player::hit(const Coords & c){
    return _shipBoard.attack(c);
}

Board Player::getBoard() const
{
    return _shipBoard;
}
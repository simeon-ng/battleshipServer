// battleship_tests.cpp
// Simeon Ng
// Jason Herning
// CS372 Software Construction
// Updated 2/26/19
// Catch2 Tests for Battleship Game

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ship.h"
#include "board.h"
#include "player.h"

TEST_CASE("Testing General Ship Functions") {

    Coords c1 = {0, 0};
    Coords c2 = {2, 0};
    Coords c3 = {4, 4};
    Coords c4 = {4, 8};

    Ship testShip1(c1, c2);
    Ship testShip2(c3, c4);

    SECTION("Length = 2, Begin = (0, 0), End = (2, 0)")
    REQUIRE(testShip1.getLength() == 3);
    REQUIRE(testShip1.getBegin() == c1);
    REQUIRE(testShip1.getEnd() == c2);

    SECTION("Length = 5, Begin = (4, 4), End = (4, 8)")
    REQUIRE(testShip2.getLength() == 5);
    REQUIRE(testShip2.getBegin() == c3);
    REQUIRE(testShip2.getEnd() == c4);

    c2.x = 1, c2.y = 0;
    c3.x = 2, c3.y = 0;
    testShip1.attack(c1);
    testShip1.attack(c2);
    testShip1.attack(c3);

    c1.x = 4, c1.y = 4;
    c2.x = 4, c2.y = 5;
    testShip2.attack(c1);
    testShip2.attack(c2);

    SECTION("Test Hitting the Ship")
    REQUIRE(testShip1.isSunk());
    REQUIRE(!testShip2.isSunk());
}

TEST_CASE("Testing Board Size, Coordinates, and Ships") {

    Board board1;
    SECTION("Default Size is 10x10 = 100 Tiles")
    REQUIRE(board1.size() == 100);

    Board board2(6);
    SECTION("1-Param Ctor")
    REQUIRE(board2.size() == 36);

    Board board3(8, 6);
    SECTION("2-Param Ctor")
    REQUIRE(board3.size() == 48);

    Coords c1 = {0, 0};
    Coords c2 = {2, 0};
    Coords c3 = {4, 4};
    Coords c4 = {4, 8};

    Ship testShip1(c1, c2);
    Ship testShip2(c3, c4);

    board1.addShip(testShip1);
    Coords c5 = {1, 0};
    SECTION("Adding a length 2 ship horizontally to the board.")
    REQUIRE(board1.isCoordTakenShip(c5));

    board2.addShip(testShip2);
    Coords c6 = {4, 9};
    SECTION("Adding a length 5 ship vertically to the board.")
    REQUIRE_FALSE(board2.isCoordTakenShip(c6));

    SECTION("Attacking board1 at (1, 0)")
    REQUIRE(board1.attack(c5));

    Coords c7 = {0, 1};
    SECTION("Attacking board1 at (0, 1)")
    REQUIRE_FALSE(board1.attack(c7));

    board1.attack(c1), board1.attack(c2), board1.attack(c5);
    SECTION("Attacking (0, 0), (1, 0) and (2, 0) sinks ship")
    REQUIRE(board1.isSunk(testShip1));
    REQUIRE(board1.allSunk());
}

TEST_CASE("Testing Player Class: Firing at opponent.") {

    Player p1;
    Coords c1 = {0, 0};
    Coords c2 = {2, 0};
    Coords c3 = {4, 4};
    Coords c4 = {4, 8};
    Ship testShip1(c1, c2);
    Ship testShip2(c3, c4);
    p1.addShip(testShip1);
    p1.addShip(testShip2);

    Coords c5 = {1, 0};
    Coords c6 = {0, 1};
    SECTION("Firing at (1, 0)")
    REQUIRE(p1.hit(c5));
    SECTION("Firing at (0, 1)")
    REQUIRE_FALSE(p1.hit(c6));
}
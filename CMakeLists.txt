cmake_minimum_required(VERSION 3.0)
project(Battleship)
project(Battleship_tests)

set(CMAKE_CXX_STANDARD_17)

include_directories(.)

#with test
add_executable(Battleship_tests
        catch.hpp
        battleship_tests.cpp
        ship.cpp ship.h
        board.cpp board.h
        player.cpp player.h
        game.cpp game.h network.h)

#with main
add_executable(Battleship
        main.cpp
        ship.cpp ship.h
        board.cpp board.h
        player.cpp player.h
        game.cpp game.h
        client.cpp client.h
        server.cpp server.h
        serverGame.cpp serverGame.h
        clientGame.cpp clientGame.h
        networkData.h)

if(WIN32)
    target_link_libraries(Battleship wsock32 ws2_32)
endif()

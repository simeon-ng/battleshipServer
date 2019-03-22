// server.h
// Simeon Ng
// Updated 3/21/19
// Header for Battleship server class

#ifndef BATTLESHIP_SERVER_H
#define BATTLESHIP_SERVER_H

#define _WIN32_WINNT 0x501          // used by ws2tcpip.h

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <cstdlib>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

// Constants and library links.
#define DEFAULT_BUFFER_LEN 512      // Size of buffer
#define DEFAULT_PORT "54000"        // Port for socket connections

class Server {

public:
    Server();
    ~Server() = default;

private:
    int _result;                // For return values.
    SOCKET _listeningSocket;    // Socket that listens to client connections (Server Socket).
    SOCKET _clientSocket;       // Socket to give to clients.
};


#endif //BATTLESHIP_SERVER_H

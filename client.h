// client.h
// Simeon Ng
// Header file for Battleship client class

#ifndef BATTLESHIP_CLIENT_H
#define BATTLESHIP_CLIENT_H

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
#include <iostream>
#include "networkData.h"
#include "network.h"

using std::cout;
using std::endl;

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

// Constants and library links.
#define DEFAULT_BUFFER_LEN 512      // Size of buffer
#define DEFAULT_PORT "54000"        // Port for socket connections

// Class : Client
// Handles connecting the client to the server.

class Client {

public:
    Client();
    ~Client() = default;
    int receivePackets(char *);

    SOCKET getConnectSocket();

private:
    int _result;                // Will hold result of return values of:
                                //      WSAStartup()
                                //      getaddrinfo()
    SOCKET _ConnectSocket;      // Client Socket
};


#endif //BATTLESHIP_CLIENT_H

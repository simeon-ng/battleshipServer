// client.cpp
// Simeon Ng
// Updated 3/21/19
// Source file for Battleship client class

#include <iostream>
#include "client.h"

// Client ctor
Client::Client() {

    // WSADATA object. Contains info about the Windows Socket implementation.
    WSADATA wsaData;

    // socket
    _ConnectSocket = INVALID_SOCKET;

    // Initialize Winsock
    _result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (_result != 0) {
        printf("WSAStartup failed: %d\n", _result);
        exit(1);
    }

    // struct addrinfo
    // Holds host address information.
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));   // Fill block of memory with zeros.
    hints.ai_family = AF_UNSPEC;         // Address family is unspecified.
    hints.ai_socktype = SOCK_STREAM;     // Socket type: Streaming socket. Used for TCP.
    hints.ai_protocol = IPPROTO_TCP;     // Protocol: TCP

    // Resolve the server address and port
    _result = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (_result != 0) {
        printf("getaddrinfo failed: %d\n", _result);
        WSACleanup();
        exit(1);
    }

    // Create a socket. Connects to the address returned by getaddrinfo()
    ptr = result;
    _ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (_ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    // Connecting to server.
    _result = connect(_ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (_result == SOCKET_ERROR) {
        closesocket(_ConnectSocket);
        _ConnectSocket = INVALID_SOCKET;
    }

    // Free address information.
    freeaddrinfo(result);

    if (_ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        exit(1);
    }
}

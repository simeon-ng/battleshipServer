// server.cpp
// Simeon Ng
// Updated 3/21/19
// Source file for Battleship server class.

#include <iostream>
#include "server.h"

Server::Server() {

// WSADATA object. Contains info about the Windows Socket implementation.
    WSADATA wsaData;

    // Initialize Winsock
    _result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (_result != 0) {
        printf("WSAStartup failed: %d\n", _result);
        exit(1);
    }

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));  // Fill block of memory with zeros.
    hints.ai_family = AF_UNSPEC;        // Unspecified address family.
    hints.ai_socktype = SOCK_STREAM;    // Socket Type: Streaming Socket. Used for TCP.
    hints.ai_protocol = IPPROTO_TCP;    // Protocol: TCP.
    hints.ai_flags = AI_PASSIVE;        // Socket address will be used in a call to bindfunction.

    // Resolve the local address and port to be used by the server
    _result = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (_result != 0) {
        printf("getaddrinfo failed: %d\n", _result);
        WSACleanup();
        exit(1);
    }

    // Create Socket that listens to client connections.
    _listeningSocket = INVALID_SOCKET;

    _listeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (_listeningSocket == INVALID_SOCKET) {
        printf("Error at socket(): %d\n", WSAGetLastError());
        freeaddrinfo(result);
    }

    // Bind TCP Listening socket
    _result = bind(_listeningSocket, result->ai_addr, (int)result->ai_addrlen);
    if (_result == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(_listeningSocket);
        WSACleanup();
        exit(1);
    }

    // Free address information
    freeaddrinfo(result);

    // Allow incoming connection requests by listening.
    if (listen(_listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(_listeningSocket);
        WSACleanup();
        exit(1);
    }
}

// acceptClient()
// Accepts clients that attempt to connect.
bool Server::acceptClient(unsigned int & id) {
    _clientSocket = accept(_listeningSocket, NULL, NULL);
    if (_clientSocket != INVALID_SOCKET) {
        // Disable nagle algorithm for client socket.
        char value = 1;
        setsockopt(_clientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
        // Add client socket to table.
        _sessions.insert(std::pair<unsigned int, SOCKET>(id, _clientSocket));
        return true;
    }
    return false;
}
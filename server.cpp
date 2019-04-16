// server.cpp
// Simeon Ng
// Source file for Battleship server class.

#include "server.h"
#include "network.h"

Server::Server() {

// WSADATA object. Contains info about the Windows Socket implementation.
    WSADATA wsaData;

    // Initialize Winsock
    _result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (_result != 0) {
        cout << "WSAStartup failed: " << _result << endl;
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
        cout << "getaddrinfo failed: " << _result << endl;
        WSACleanup();
        exit(1);
    }

    // Create Socket that listens to client connections.
    _listeningSocket = INVALID_SOCKET;

    _listeningSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (_listeningSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        freeaddrinfo(result);
    }

    // Bind TCP Listening socket
    _result = bind(_listeningSocket, result->ai_addr, (int)result->ai_addrlen);
    if (_result == SOCKET_ERROR) {
        cout << "bind() failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        closesocket(_listeningSocket);
        WSACleanup();
        exit(1);
    }

    // Free address information
    freeaddrinfo(result);

    // Allow incoming connection requests by listening.
    if (listen(_listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen failed with error: " << WSAGetLastError() << endl;
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

// receiveData()
// Reads message on server side.
int Server::receiveData(unsigned int clientID, char * recvBuffer) {
    if (_sessions.find(clientID) != _sessions.end()) {
        SOCKET currentSocket = _sessions[clientID];
        _result = receiveMessage(currentSocket, recvBuffer, MAX_PACKET_SIZE);

        if (_result == 0) {
            cout << "Connection closed" << endl;
            _sessions.clear();
            _result = shutdown(currentSocket, SD_SEND);

            if(_result == SOCKET_ERROR) {
                cout << "Shutdown failed: " << WSAGetLastError() << endl;
                closesocket(currentSocket);
                WSACleanup();
                return 1;
            }
            closesocket(currentSocket);
            WSACleanup();
            return _result;
            //TODO: Remove clients from sessions, shutdown socket.
        }
        return _result;
    }
    return 0;
}

// sendToAllClients()
// Sends action packets to all clients.
void Server::sendToAllClients(char * packets, int totalSize) {
    SOCKET currentSocket;
    for(auto iter : _sessions) {
        currentSocket = iter.second;
        _result = sendMessage(currentSocket, packets, totalSize);
        if (_result == SOCKET_ERROR) {
            cout << "Send failed with error: " << WSAGetLastError() << endl;
            closesocket(currentSocket);
        }
    }

}


std::map<unsigned int, SOCKET> Server::getSessions() {
    return _sessions;
}

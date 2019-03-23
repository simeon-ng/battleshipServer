// client.cpp
// Simeon Ng
// Source file for Battleship client class

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
        cout << "WSAStartup failed: " << _result << endl;
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
        cout << "getaddrinfo failed: " << _result << endl;
        WSACleanup();
        exit(1);
    }

    // Create a socket. Connects to the address returned by getaddrinfo()
    ptr = result;
    _ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (_ConnectSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
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
        cout << "Unable to connect to server!" << endl;
        WSACleanup();
        exit(1);
    }

    // Setup the socket to be nonblocking.
    // Means it will not wait on send and receive functions when
    // there is no data to send/receive.
    u_long mode = 1;
    _result = ioctlsocket(_ConnectSocket, FIONBIO, &mode);
    if (_result == SOCKET_ERROR) {
        cout << "ioctlsocket failed with error " << WSAGetLastError() << endl;
        closesocket(_ConnectSocket);
        WSACleanup();
        exit(1);
    }

    // Disable nagle.
    // nagle is an algorithm that reduces the amount of packets set over the network.
    char value = 1;
    setsockopt(_ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

// receivePackets()
// Receives packets from the server.
int Client::receivePackets(char * recvBuffer) {
    _result = receiveMessage(_ConnectSocket, recvBuffer, MAX_PACKET_SIZE);
    if (_result == 0) {
        cout << "Connection closed." << endl;
        closesocket(_ConnectSocket);
        WSACleanup();
        exit(1);
    }
    return _result;
}

SOCKET Client::getConnectSocket() {
    return _ConnectSocket;
}

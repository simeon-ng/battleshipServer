// network.h
// Simeon Ng
// Header file for send and receive functions.

#ifndef BATTLESHIP_NETWORK_H
#define BATTLESHIP_NETWORK_H

#include <winsock2.h>
#include <windows.h>

// sendMessage()
// Calls send() of the winsock library.
// Sends data through the socket.
static int sendMessage(SOCKET currentSocket, char * message, int messageSize) {
    return send(currentSocket, message, messageSize, 0);
}

// receiveMessage()
// Calls recv() of the winsock library.
// Receives data from a socket.
static int receiveMessage(SOCKET currentSocket, char * buffer, int bufferSize) {
    return recv(currentSocket, buffer, bufferSize, 0);
}

#endif //BATTLESHIP_NETWORK_H

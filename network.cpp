// network.cpp
// Simeon Ng
// Updated 3/21/19

#include "network.h"

// sendMessage()
// Calls send() of the winsock library.
// Sends data through the socket.
int Network::sendMessage(SOCKET currentSocket, char * message, int messageSize) {
    return send(currentSocket, message, messageSize, 0);
}

// receiveMessage()
// Calls recv() of the winsock library.
// Receives data from a socket.
int Network::receiveMessage(SOCKET currentSocket, char * buffer, int bufferSize) {
    return recv(currentSocket, buffer, bufferSize, 0);
}
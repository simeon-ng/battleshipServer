// network.h
// Simeon Ng
// Updated 3/21/19

#ifndef BATTLESHIP_NETWORK_H
#define BATTLESHIP_NETWORK_H

#include <winsock2.h>
#include <windows.h>

// Class : Network
class Network {

public:

    static int sendMessage(SOCKET, char *, int);
    static int receiveMessage(SOCKET, char *, int);

};


#endif //BATTLESHIP_NETWORK_H

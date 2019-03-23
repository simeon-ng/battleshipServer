// clientGame.cpp
// Simeon Ng
// Source file for ClientGame class.

#include "clientGame.h"
#include "network.h"

ClientGame::ClientGame() {
    _network = std::make_unique<Client>();

    // Initial connection to server.
    const unsigned int packetSize = sizeof(Packet);
    char packetData[packetSize];

    Packet packet;
    packet._packetType = INIT_CONNECTION;

    packet.serialize(packetData);

    sendMessage(_network->getConnectSocket(), packetData, packetSize);
}

// sendActionPackets()
// Sends action packets to server.
void ClientGame::sendActionPackets() {
    const unsigned int packetSize = sizeof(Packet);
    char packetData[packetSize];

    Packet packet;
    packet._packetType = ACTION_EVENT;

    packet.serialize(packetData);
    sendMessage(_network->getConnectSocket(), packetData, packetSize);
}

// update()
// Continuously receives action packets from server and sends packets in response.
void ClientGame::update() {
    Packet packet;
    int dataLen = _network->receivePackets(_networkData);
    if (dataLen <= 0) {
        return;
    }

    int index = 0;
    while (index < (unsigned int)dataLen) {
        packet.deserialize(&(_networkData[index]));
        index += sizeof(Packet);

        switch(packet._packetType) {
            case ACTION_EVENT:
                cout << "Client received Action event packet from server." << endl;
                sendActionPackets();
                break;
            default:
                cout << "Error in packet types." << endl;
                break;
        }
    }
}
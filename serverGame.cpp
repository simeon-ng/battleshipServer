// serverGame.cpp
// Simeon Ng
// Source file for ServerGame class.

#include "serverGame.h"

unsigned int ServerGame::_clientID;
ServerGame::ServerGame() {
    _clientID = 0;
    _network = std::make_unique<Server>();
}

// update()
// Continuously accept new clients and assign them to an ID.
void ServerGame::update() {
    if (_network->acceptClient(_clientID)) {
        cout << "Client " << _clientID << " has connected to the server." << endl;
        _clientID++;
    }
    receiveFromClient();
}

// receiveFromClient()
// Receives data from all clients in _network->_sessions.
void ServerGame::receiveFromClient() {
    Packet packet;

    for(auto iter : _network->getSessions()) {
        int dataLen = _network->receiveData(iter.first, _networkData);
        if (dataLen <= 0) {
            continue;
        }

        int index = 0;
        while (index < (unsigned int)dataLen) {
            packet.deserialize(&(_networkData[index]));
            index += sizeof(Packet);

            switch(packet._packetType) {
                case INIT_CONNECTION:
                    cout << "Server received INIT packet from client." << endl;
                    sendActionPackets();
                    break;
                case ACTION_EVENT:
                    cout << "Server received Action event packet from client." << endl;
                    sendActionPackets();
                    break;
                default:
                    cout << "Error in packet types." << endl;
                    break;
            }
        }
    }
}

// sendActionPackets()
// Sends action packets to all connected clients.
void ServerGame::sendActionPackets() {
    const unsigned int packetSize = sizeof(Packet);
    char packetData[packetSize];

    Packet packet;
    packet._packetType = ACTION_EVENT;

    packet.serialize(packetData);
    _network->sendToAllClients(packetData, packetSize);
}

// sendPrompt()
// Sends a simple prompt to the clients.
void ServerGame::sendPrompt() {
    const unsigned int packetSize = sizeof(Packet);
    // TODO
}
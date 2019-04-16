// networkData.h
// Simeon Ng
// Header file for Network Data / Packet types.

#ifndef BATTLESHIP_NETWORKDATA_H
#define BATTLESHIP_NETWORKDATA_H

#include <cstring>

#define MAX_PACKET_SIZE 1000000

enum PacketTypes {
    INIT_CONNECTION = 0, ACTION_EVENT = 1, PROMPT_EVENT = 2
};

struct Packet {
     unsigned int _packetType;

     // serialize()
     // Converts _packetType data into bytes to send over the network.
     void serialize(char * data) {
         memcpy(data, this, sizeof(Packet));
     }

     // deserialize()
     // Converts bytes received over the network to
     // _packetType data we can interpret.
     void deserialize(char * data) {
         memcpy(this, data, sizeof(Packet));
     }

     // serializePrompt()
     void serializePrompt();
     // TODO
};

#endif //BATTLESHIP_NETWORKDATA_H

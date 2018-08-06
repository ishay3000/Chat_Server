//
// Created by Ishay Cena on 22/07/2018.
//

#ifndef ECHO_SERVER_DATA_H
#define ECHO_SERVER_DATA_H

#include <winsock2.h>

typedef SOCKET Socket;

typedef enum Status{
    OK, REGISTER, QUIT, ERR_FORCE_QUIT, ERR_REGISTER
//    OK, ERR, QUIT, USERS_LIST, REGISTER
}Status;

#pragma pack(push, 1)

typedef struct Header{
    // packet size
    int dataSize;

    // sender's name
    char source[15];

    // destination user's name
    char destination[15];

    // TODO consider using a message status
    Status status = OK;
}Header;

typedef struct Packet{
    char dataBuffer[512];
}Packet;

typedef struct Message{
    Header header;
    Packet packet;
}Message;
#pragma pack(pop)

const size_t HEADER_SIZE = sizeof(Header);

#endif //ECHO_SERVER_DATA_H

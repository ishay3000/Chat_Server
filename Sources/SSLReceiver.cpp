//
// Created by Ishay Cena on 26/07/2018.
//

#include <cstdio>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include "../Headers/SSLReceiver.h"

Message SSLReceiver::Receive(SSL *sslClient) {
    Message message;
    Header header;
    Packet packet;

    header = ReceiveHeader(sslClient);
    if(header.status == OK) {
        // only get packet if header is ok
        packet = ReceivePacket(sslClient, header);
    }
    message.header = header;
    message.packet = packet;

    return message;
}

Header SSLReceiver::ReceiveHeader(SSL *sslClient) {
    int totalBytes = HEADER_SIZE;
    int bytesReceived = 0;
    int bytesLeft = totalBytes;
    int bytes = 0;
    char buffer[HEADER_SIZE] = {0};
    Header header;

    while(bytesLeft) {
        bytes = SSL_read(sslClient, buffer, bytesLeft);
        if (bytes > 0) {
            bytesReceived += bytes;
            bytesLeft -= bytes;
        } else {
            // user force closed the chat. Indicate in the header for an ERR_FORCE_QUIT
            header.status = ERR_FORCE_QUIT;
//            Socket clientSock = SSL_get_fd(sslClient);
//            printf("[-] Client %d forcefully disconnected.\n", clientSock);
//            SSL_free(sslClient);
            return header;
        }
    }// finished reading header
    memcpy(&header, buffer, HEADER_SIZE);
    return header;
}

Packet SSLReceiver::ReceivePacket(SSL *sslClient, Header &header) {
    int totalBytes = header.dataSize;
    int bytesReceived = 0;
    int bytesLeft = totalBytes;
    int bytes = 0;
    char buffer[header.dataSize] = {0};
    Packet packet;

    while(bytesLeft) {
        bytes = SSL_read(sslClient, buffer, bytesLeft);
        if (bytes > 0) {
            bytesReceived += bytes;
            bytesLeft -= bytes;
        } else {
            // user force closed the chat. Indicate in the header for an ERR_FORCE_QUIT
            header.status = ERR_FORCE_QUIT;
//            Socket clientSock = SSL_get_fd(sslClient);
//            printf("[-] Client %d forcefully disconnected.\n", clientSock);
//            SSL_free(sslClient);
            return packet;
        }
    }// finished reading header
    memcpy(&packet, buffer, header.dataSize);
    return packet;
}

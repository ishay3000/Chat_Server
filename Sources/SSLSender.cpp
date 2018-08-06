//
// Created by Ishay Cena on 26/07/2018.
//

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <vector>
#include "../Headers/SSLSender.h"

bool SSLSender::Send(SSL *sslClient, Message message) {
    if (SendHeader(sslClient, message.header)){
        if (SendPacket(sslClient, message.packet, message.header)){
            return true;
        }
    }
    return false;
}

bool SSLSender::SendHeader(SSL *sslClient, Header &header) {
    int totalBytes = HEADER_SIZE;
    int bytesReceived = 0;
    int bytesLeft = totalBytes;
    int bytes = 0;
    char buffer[HEADER_SIZE];
    memcpy(buffer, &header, HEADER_SIZE);

    while(bytesLeft) {
        bytes = SSL_write(sslClient, buffer, bytesLeft);
        if (bytes > 0) {
            bytesReceived += bytes;
            bytesLeft -= bytes;
        } else {
            Socket clientSock = SSL_get_fd(sslClient);
            printf("[-] Client %d disconnected\n", clientSock);
            SSL_free(sslClient);
            return false;
        }
    }// finished sending header
    return true;
}

bool SSLSender::SendPacket(SSL *sslClient, Packet &packet, Header &header) {
    int totalBytes = header.dataSize;
    int bytesReceived = 0;
    int bytesLeft = totalBytes;
    int bytes = 0;
    char buffer[header.dataSize];
    memcpy(buffer, &packet, header.dataSize);

    while(bytesLeft) {
        bytes = SSL_write(sslClient, buffer, bytesLeft);
        if (bytes > 0) {
            bytesReceived += bytes;
            bytesLeft -= bytes;
        } else {
            Socket clientSock = SSL_get_fd(sslClient);
            printf("[-] Client %d disconnected\n", clientSock);
            SSL_free(sslClient);
            return false;
        }
    }// finished sending packet
    return true;
}

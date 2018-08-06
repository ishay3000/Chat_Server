//
// Created by Ishay Cena on 30/07/2018.
//


#include "../includes/includes.h"
#include "../Headers/ClientHandlerEcho.h"


ClientHandlerEcho::ClientHandlerEcho(SSLSender &sender, SSLReceiver &receiver)
        : IClientHandler(sender, receiver) {

}


void ClientHandlerEcho::Handle(SSL *sslClient) {

    bool isSuccessfulSent;
    Message message;

    while (true) {
        ZeroMemory(&message, sizeof(message));
        // get the message
        message = m_receiver.Receive(sslClient);
        printf("Client >> %s\n", message.packet.dataBuffer);
        if (!strcmp(message.packet.dataBuffer, "quit")) {
            Socket clientSock = static_cast<Socket>(SSL_get_fd(sslClient));
            printf("[-] Client %d disconnected", clientSock);
            SSL_free(sslClient);
            break;
        }
        // echo it back to the client
        isSuccessfulSent = m_sender.Send(sslClient, message);
        if (!isSuccessfulSent) {
            perror("Failed to send message to the client");
            break;
        }
    }
}
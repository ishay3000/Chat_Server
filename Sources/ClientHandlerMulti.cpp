//
// Created by Ishay Cena on 30/07/2018.
//

#include "../Headers/ClientHandlerMulti.h"
#include "../Headers/ChatLogger.h"

ClientHandlerMulti::ClientHandlerMulti(SSLSender &sender, SSLReceiver &receiver) : IClientHandler(sender, receiver) {

}

void ClientHandlerMulti::Handle(SSL *sslClient) {
    bool isSuccessfulSent;
    bool isDestinationExists;
    Message message;

    // get the user's name and add it to the map of names
    Message msgHeaderUsername = m_receiver.Receive(sslClient);
    m_mapClients[string(msgHeaderUsername.header.source)] = sslClient;
    printf("[+] added client <<%d>>--<<%s>>", SSL_get_fd(sslClient), msgHeaderUsername.header.source);
    ChatLogger::Log(msgHeaderUsername, LOGIN);

    while (true) {
        ZeroMemory(&message, sizeof(message));

        // get the message
        message = m_receiver.Receive(sslClient);
        Status status = message.header.status;
        if (status == ERR_FORCE_QUIT || status == QUIT){
            printf("Client quit. Deleting entry [%s]", msgHeaderUsername.header.source);
            ChatLogger::Log(msgHeaderUsername, LOGOUT);

            // user quit
            int erased = m_mapClients.erase(msgHeaderUsername.header.source /*message.header.source*/);
            if (erased > 0) {
                printf("deleted entry [%s]", msgHeaderUsername.header.source /*message.header.source*/);
            } else {
                printf("couldn't delete entry");
            }
            break;
        }
        // check if destination exists in the map
        isDestinationExists = (m_mapClients.count(message.header.destination) > 0);
        if (isDestinationExists) {
            // such user exists
            ChatLogger::Log(message);

            SSL *destinationUser = m_mapClients[string(message.header.destination)];
            isSuccessfulSent = m_sender.Send(destinationUser, message);
            if (!isSuccessfulSent) {
                printf("[-] failed to deliver message from %s to %s",
                       message.header.source, message.header.destination);
            }
        }
    }
    printf("[-] Client %s closed the connection.", msgHeaderUsername.header.source);
}
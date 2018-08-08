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

    // try to register the client
    Message msgHeaderUsername = Register(sslClient);
    // add the name/socket to the map
    UpdateMap(msgHeaderUsername.header.source, sslClient, ADD);

//    m_mapClients[string(msgHeaderUsername.header.source)] = sslClient;
    printf("[+] added client <<%d>>\t<<%s>>", SSL_get_fd(sslClient), msgHeaderUsername.header.source);
    ChatLogger::Log(msgHeaderUsername, LOGIN);

    while (true) {
        // get the message
        Message message = m_receiver.Receive(sslClient);
        Status status = message.header.status;
        if (status == ERR_FORCE_QUIT || status == QUIT){
            // user quit
            printf("Client quit. Deleting entry [%s]", msgHeaderUsername.header.source);
            ChatLogger::Log(msgHeaderUsername, LOGOUT);
            // remove name/socket from the map
            UpdateMap(msgHeaderUsername.header.source, sslClient, REMOVE);

/*            int erased = m_mapClients.erase(msgHeaderUsername.header.source *//*message.header.source*//*);
            if (erased > 0) {
                printf("deleted entry [%s]", msgHeaderUsername.header.source *//*message.header.source*//*);
            } else {
                printf("couldn't delete entry");
            }*/
            break;
        }
        // check if destination exists in the map
        if (IsNameExists(message.header.destination)) {
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

Message ClientHandlerMulti::Register(SSL *ssl) {
    Message nameMessage;
    Header header;
    Packet packet;

    while (true){
        nameMessage = m_receiver.Receive(ssl);
        if  (!this->IsNameExists(nameMessage.header.source)){
            // if name doesn't exist
            header.status = OK;
            header.dataSize = 0;
            Message msg = {header ,packet};
            // send the OK status
            m_sender.Send(ssl, msg);
            // return the message containing the valid name back to the handler thread
            return nameMessage;
        } else{
            header.status = ERR_REGISTER;
            header.dataSize = 0;
            m_sender.Send(ssl, Message {header, packet});
        }
    }
}

bool ClientHandlerMulti::IsNameExists(const char *name) {
    bool isDestinationExists = (m_mapClients.count(string(name)) > 0);
    return isDestinationExists;
}

static mutex mapMutex;
void ClientHandlerMulti::UpdateMap(const char *name, SSL *ssl, MapAction action) {
    unique_lock<mutex> lock(mapMutex);

    switch (action){
        case ADD:
            m_mapClients[string(name)] = ssl;
            break;
        case REMOVE:
            int erased = m_mapClients.erase(name);
/*            if (erased > 0){

            }*/
            break;
    }
}

//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H
#define INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H


#include "IClientHandler.h"
#include "../includes/includes.h"

typedef enum MapAction{
    ADD, REMOVE
}MapAction;

class ClientHandlerMulti : public IClientHandler {
public:
    ClientHandlerMulti(SSLSender &sender, SSLReceiver &receiver);

    void Handle(SSL *ssl) override;

private:
    std::map<string, SSL *> m_mapClients;

    /**
     * updates the names/sockets hash-map to add or remove a client
     * @param name the name
     * @param ssl the client socket
     * @param action the action (ADD/REMOVE)
     */
    void UpdateMap(const char *name, SSL *ssl, MapAction action);

    /**
     * tries to register the newly added client to the server
     * @param ssl the new client socket
     * @return a message containing the user name
     */
    Message Register(SSL *ssl);

    /**
     * Checks whether a name exists while registering a new client
     * @param name the name sent to check
     * @return if the name exists or not
     */
    bool IsNameExists(const char *name);
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H

//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H
#define INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H


#include "IClientHandler.h"
#include "../includes/includes.h"

class ClientHandlerMulti : public IClientHandler {
public:
    ClientHandlerMulti(SSLSender &sender, SSLReceiver &receiver);

    void Handle(SSL *ssl) override;

private:
    std::map<string, SSL *> m_mapClients;
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERMULTI_H

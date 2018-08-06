//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERECHO_H
#define INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERECHO_H


#include "IClientHandler.h"

class ClientHandlerEcho : public IClientHandler {
public:
    ClientHandlerEcho(SSLSender &sender, SSLReceiver &receiver);

    void Handle(SSL *ssl) override;
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_CLIENTHANDLERECHO_H

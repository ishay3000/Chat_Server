//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_ICLIENTHANDLER_H
#define INHERITANCE_SERVER_ATTEMPT_1_ICLIENTHANDLER_H


#include <openssl/ossl_typ.h>
#include "SSLSender.h"
#include "SSLReceiver.h"

class IClientHandler {
public:
    IClientHandler(SSLSender &sender, SSLReceiver &receiver);
    ~IClientHandler() = default;
    /**
     * handles the communication with the client
     * @param sslClient the client socket
     */
    virtual void Handle(SSL *sslClient) = 0;

protected:
    SSLSender m_sender;
    SSLReceiver m_receiver;

    void Foo() {}
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_ICLIENTHANDLER_H

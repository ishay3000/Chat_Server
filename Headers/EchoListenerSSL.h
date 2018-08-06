//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_ECHOLISTENERSSL_H
#define INHERITANCE_SERVER_ATTEMPT_1_ECHOLISTENERSSL_H


#include "ListenerSSL.h"
#include "ClientHandlerEcho.h"

class EchoListenerSSL : public ListenerSSL {
public:

    explicit EchoListenerSSL(IClientHandler &handler);

    void StartListening(const char*address, int port) override;

};


#endif //INHERITANCE_SERVER_ATTEMPT_1_ECHOLISTENERSSL_H

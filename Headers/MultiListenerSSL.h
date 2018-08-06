//
// Created by Ishay Cena on 30/07/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_MULTILISTENERSSL_H
#define INHERITANCE_SERVER_ATTEMPT_1_MULTILISTENERSSL_H


#include "ListenerSSL.h"

class MultiListenerSSL : public ListenerSSL {
public:
    explicit MultiListenerSSL(IClientHandler &handler);
    void StartListening(const char *address, int port) override;
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_MULTILISTENERSSL_H

//
// Created by Ishay Cena on 27/07/2018.
//

#ifndef ECHO_SERVER_FINALE_IRECEIVE_H
#define ECHO_SERVER_FINALE_IRECEIVE_H


#include "../includes/Data.h"

template <typename T>
class IReceiver {
    /**
     * Receives the message from the client socket
     * @param clientSocket the client socket
     * @return the message received by the client socket
     */
    virtual Message Receive(T *clientSocket) = 0;
};


#endif //ECHO_SERVER_FINALE_IRECEIVE_H

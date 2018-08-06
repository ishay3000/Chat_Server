//
// Created by Ishay Cena on 27/07/2018.
//

#ifndef ECHO_SERVER_FINALE_ISENDER_H
#define ECHO_SERVER_FINALE_ISENDER_H

#include "../includes/Data.h"

template <typename T>
class ISender {
public:
    /**
 * sends a Message to the client socket
 * @param clientSocket the ssl client socket
 * @param message the message to send
 * @return if the message was sent
 */
    virtual bool Send(T *clientSocket, Message message) = 0;
};


#endif //ECHO_SERVER_FINALE_ISENDER_H

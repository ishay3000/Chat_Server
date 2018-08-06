//
// Created by Ishay Cena on 26/07/2018.
//

#ifndef ECHO_SERVER_FINALE_ILISTENER_H
#define ECHO_SERVER_FINALE_ILISTENER_H

#include <openssl/ossl_typ.h>
#include "../includes/Data.h"

class IListener{
private:
    /**
     * binds the server to address and port
     * @param address the address to bind on
     * @param port the port to bind on
     * @return bind status
     */
    virtual bool Bind(const char* address, int port) = 0;
    /**
     * listens for connections using the server socket
     * @return listen status
     */
    virtual bool Listen() = 0;
    /**
     * accepting a client connection
     * @return the SSL client socket
     */
    virtual Socket Accept() = 0;

public:
    IListener() = default;
    /**
 * start listening for connections
 * @param address the address to listen on
 * @param port the port to listen on
 */
    virtual void StartListening(const char* address, int port) = 0;
    virtual ~IListener() = default;
};

#endif //ECHO_SERVER_FINALE_ILISTENER_H

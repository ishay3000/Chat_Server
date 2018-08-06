//
// Created by Ishay Cena on 26/07/2018.
//

#ifndef ECHO_SERVER_FINALE_SERVER_H
#define ECHO_SERVER_FINALE_SERVER_H


#include "IListener.h"
#include "ListenerSSL.h"
#include <winsock2.h>

class Server {
public:
    Server(ListenerSSL &listener, const char *address, const int &port);
    ~Server();

    /**
     * Runs the server's listener
     */
    void Run();

protected:
    ListenerSSL &m_listener;
    const char *m_address;
    const int &m_port;

    /**
     * initiates the WinSock service
     * @return if WinSock init was successful
     */
    bool InitWinSock();
};


#endif //ECHO_SERVER_FINALE_SERVER_H

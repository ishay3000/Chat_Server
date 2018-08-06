//
// Created by Ishay Cena on 26/07/2018.
//

#ifndef ECHO_SERVER_FINALE_SSLRECEIVER_H
#define ECHO_SERVER_FINALE_SSLRECEIVER_H


#include <openssl/ossl_typ.h>
#include "../includes/Data.h"
#include "IReceiver.h"

class SSLReceiver : public IReceiver<SSL> {
public:
    SSLReceiver() = default;
    ~SSLReceiver() = default;
    Message Receive(SSL* sslClient) override;

private:
    /**
     * Receives the header from the client socket
     * @param sslClient the client socket
     * @return the header received
     */
    Header ReceiveHeader(SSL *sslClient);

    /**
     * Called after ::ReceiveHeader(SSL *sslClient). <p>
     * Receives the packet using the info in the header previously received.
     * @param sslClient the client socket
     * @param header the header previously received
     * @return the packet received
     */
    Packet ReceivePacket(SSL *sslClient, Header &header);
};


#endif //ECHO_SERVER_FINALE_SSLRECEIVER_H

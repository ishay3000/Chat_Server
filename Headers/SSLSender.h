//
// Created by Ishay Cena on 26/07/2018.
//

#ifndef ECHO_SERVER_FINALE_SSLSENDER_H
#define ECHO_SERVER_FINALE_SSLSENDER_H


#include <openssl/ossl_typ.h>
#include "../includes/Data.h"
#include "ISender.h"

class SSLSender : public ISender<SSL> {
public:
    SSLSender() = default;
    ~SSLSender() = default;

    bool Send(SSL* sslClient, Message message) override;

private:
    /**
     * sends the header to the client
     * @param sslClient the client socket
     * @param header the header to send
     * @return if the header was sent
     */
    bool SendHeader(SSL* sslClient, Header &header);
    /**
     * sends the packet to the client
     * @param sslClient the client socket
     * @param packet the packet to send
     * @param header the header of the message (for the message size)
     * @return if the packet was sent
     */
    bool SendPacket(SSL *sslClient, Packet &packet, Header &header);
};


#endif //ECHO_SERVER_FINALE_SSLSENDER_H

//
// Created by Ishay Cena on 30/07/2018.
//

#include "../Headers/MultiListenerSSL.h"

MultiListenerSSL::MultiListenerSSL(IClientHandler &handler) : ListenerSSL(handler) {

}

void MultiListenerSSL::StartListening(const char *address, const int port) {
    InitSSLMethods();
    SSL *ssl;

    if (Bind(address, port)){
        if (Listen()){
            printf("Waiting for connections...");

            while (true) {
                // accept new ssl client connection
                SOCKET client = Accept();
                ssl = SSL_new(m_ctx);              /* get new SSL state with context */
                SSL_set_fd(ssl, client);      /* set connection socket to SSL state */
                // SSL accepting the client
                if (SSL_accept(ssl) == -1)     /* do SSL-protocol accept */
                    ERR_print_errors_fp(stderr);
                ShowCerts(ssl);        /* get any certificates */

                // handle the new client
                std::thread clientThread(&IClientHandler::Handle, m_clientHandler, ssl);
                clientThread.detach();
            }
        }
    }
}
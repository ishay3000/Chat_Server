//
// Created by Ishay Cena on 26/07/2018.
//

#ifndef ECHO_SERVER_FINALE_SERVER_Listener_H
#define ECHO_SERVER_FINALE_SERVER_Listener_H


#include "IListener.h"
#include "SSLSender.h"
#include "SSLReceiver.h"
#include "../includes/includes.h"
#include "IClientHandler.h"

class ListenerSSL : public IListener {
public:
    explicit ListenerSSL(IClientHandler &handler);
    ~ListenerSSL() override;

protected:
    Socket m_server;
    SSL_CTX *m_ctx;
    IClientHandler &m_clientHandler;
    char *certificatePath = const_cast<char *>(R"(C:\Users\Ishay Cena\Documents\Visual Studio 2017\Projects\Server 1\Server 1\servercert.pem)");


    bool Bind(const char* address, int port) override;
    bool Listen() override;
    SOCKET Accept() override;


    /**
     * initiates the SSL methods to communicate with SSL clients
     */
    void InitSSLMethods();

    /**
 * initiates the ssl context
 * @return ssl context
 */
    SSL_CTX* InitServerCTX();
    /**
     * initiates ssl certificates
     * @param ctx ssl context
     * @param CertFile path to certificate
     * @param KeyFile path to certificate
     */
    void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
    /**
     * sends certificate to the client to authenticate
     * @param ssl the SSL client connection socket
     */
    void ShowCerts(SSL* ssl);

};


#endif //ECHO_SERVER_FINALE_SERVER_H

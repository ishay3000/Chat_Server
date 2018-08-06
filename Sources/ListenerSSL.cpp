//
// Created by Ishay Cena on 26/07/2018.
//


#include "../Headers/ListenerSSL.h"

ListenerSSL::ListenerSSL(IClientHandler &handler)
        : m_clientHandler(handler) {

}

SSL_CTX *ListenerSSL::InitServerCTX() {
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    //method = SSLv3_server_method();  /* create new m_server-method instance */
    ctx = SSL_CTX_new(SSLv3_method());   /* create new context from method */
    if (ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
        //abort();
    }
    return ctx;
}

void ListenerSSL::LoadCertificates(SSL_CTX *ctx, char *CertFile, char *KeyFile) {
    /* set the local certificate from CertFile */
    if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stdout);
        //system("pause");
        //abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        //abort();
    }
    /* verify private key */
    if (!SSL_CTX_check_private_key(ctx))
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        //abort();
    }
}

void ListenerSSL::ShowCerts(SSL *ssl) {
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if (cert != NULL)
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        //free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        //free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}

//void ListenerSSL::ProcessClientSSL(SSL *sslClient) {
//    // SSL accepting the client
//    if (SSL_accept(sslClient) == -1)     /* do SSL-protocol accept */
//        ERR_print_errors_fp(stderr);
//    ShowCerts(sslClient);        /* get any certificates */
//
//    bool isSuccessfulSent;
//    Message message;
//
//    while (true) {
//        ZeroMemory(&message, sizeof(message));
//        // get the message
//        message = m_receiver.Receive(sslClient);
//        printf("Client >> %s", message.packet.dataBuffer);
//        if (!strcmp(message.packet.dataBuffer, "quit")) {
//            break;
//        }
//        // echo it back to the client
//        isSuccessfulSent = m_sender.Send(sslClient, message);
//        if (!isSuccessfulSent){
//            //perror("Failed to send message to the client");
//        }
//    }
//    printf("[-] Client %s closed the connection.", message.header.source);
//    SSL_free(sslClient);
//    exit(0);
//}

bool ListenerSSL::Bind(const char *address, int port) {
    struct sockaddr_in addr;

    m_server = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(static_cast<u_short>(port));
    addr.sin_addr.s_addr = inet_addr(address);

    if (bind(m_server, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        perror("can't bind port");
        return false;
    }
    return true;
}

bool ListenerSSL::Listen() {
    if (listen(m_server, 10) != 0)
    {
        perror("Can't configure listening port");
        return false;
    }
    return true;
}

SOCKET ListenerSSL::Accept() {
    struct sockaddr_in addr;
    int len = sizeof(addr);
    SSL *ssl;
    SOCKET client = accept(m_server, (struct sockaddr*)&addr, &len);  /* accept connection as usual */
    printf("Connection: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

    return client;
}

/*void ListenerSSL::StartListening(const char *address, int port) {
    InitSSLMethods();
    SSL *ssl;

    if (Bind(address, port)){
        if (Listen()){
            printf("Waiting for connections...\n");
            while (true) {
                // accept new ssl client connection
                SOCKET client = Accept();
                ssl = SSL_new(m_ctx);              *//* get new SSL state with context *//*
                SSL_set_fd(ssl, client);      *//* set connection socket to SSL state *//*
                // start communicating with the client
//            std::thread clientThread(ProcessClientSSL, this, ssl);
//            clientThread.detach();
                std::thread t1(&SSLSender::Send, m_sender, ssl, Message());
            }
        }
    }
}*/

ListenerSSL::~ListenerSSL() {
    // clear server socket
    closesocket(m_server);
    // WinSock cleanup
    WSACleanup();
}

void ListenerSSL::InitSSLMethods() {
    SSL_library_init();
    m_ctx = InitServerCTX();
    LoadCertificates(m_ctx, certificatePath, certificatePath);

}


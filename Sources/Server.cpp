//
// Created by Ishay Cena on 26/07/2018.
//

#include "../Headers/Server.h"
#include "../includes/includes.h"
#include "../Headers/ListenerSSL.h"

Server::Server(ListenerSSL &listener, const char *address, const int &port)
        : m_listener(listener), m_address(address), m_port(port){

}

bool Server::InitWinSock() {
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
    {
        MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
        return false;
    }else{
//        printf("[-] initiated WinSock v.2\n");
        return true;
    }
}

Server::~Server() {
//    WSACleanup();
}

void Server::Run() {
    if (InitWinSock()) {
        m_listener.StartListening(m_address, m_port);
    }else{
        printf("Failed to init WinSock V.2\tShutting down...");
        exit(0);
    }
}

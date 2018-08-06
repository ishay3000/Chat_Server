#include <iostream>
#include <fstream>
#include "Headers/SSLSender.h"
#include "Headers/SSLReceiver.h"
#include "Headers/ListenerSSL.h"
#include "Headers/Server.h"
#include "includes/includes.h"
#include "Headers/EchoListenerSSL.h"
#include "Headers/ClientHandlerMulti.h"
#include "Headers/MultiListenerSSL.h"


int main() {
    SSLSender sender;
    SSLReceiver receiver;
//    ClientHandlerEcho clientHandlerEcho(sender, receiver);
//    EchoListenerSSL echoListenerSSL(clientHandlerEcho);
    ClientHandlerMulti clientHandlerMulti(sender, receiver);
    MultiListenerSSL multiListenerSSL(clientHandlerMulti);

    Server server(multiListenerSSL, "127.0.0.1", 6769);
    server.Run();

}
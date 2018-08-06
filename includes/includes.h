//
// Created by Ishay Cena on 22/07/2018.
//

#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <thread>
#include <mutex>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/bio.h"

#include "mingw.thread.h"
#include "mingw.mutex.h"
#include "mingw.shared_mutex.h"

#include <winsock2.h>
#include "Data.h"

//#include "../Headers/Server.h"

using namespace std;

#define printf(...) do{ printf(__VA_ARGS__); puts(""); } while(0)


static bool isListening = true;



#endif //ECHO_SERVER_INCLUDES_H

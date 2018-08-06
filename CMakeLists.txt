cmake_minimum_required(VERSION 3.10)
project(Inheritance_Server_attempt_1)

set(CMAKE_CXX_STANDARD 11)

include_directories(C:\\OpenSSL102-Win32\\include)
include_directories(C:\\OpenSSL102-Win32\\lib)
include_directories(C:\\OpenSSL102-Win32)
link_directories(C:\\OpenSSL-Win32\\lib\\MinGW)

set(OPENSSL_ROOT_DIR=C:\\OpenSSL102-Win32)
set(OPENSSL_INCLUDE_DIR=C:\\OpenSSL102-Win32\\include)
set(OPENSSL_LIBRARIES=C:\\OpenSSL102-Win32\\lib)

#include_directories(Headers)
#include_directories(Sources)

link_libraries(ws2_32 wsock32)

add_executable(Inheritance_Server_attempt_1 main.cpp includes/includes.h includes/Data.h
        includes/mingw.thread.h includes/mingw.mutex.h includes/mingw.shared_mutex.h
        Headers/IListener.h Sources/ListenerSSL.cpp Headers/ListenerSSL.h
        Sources/Server.cpp Headers/Server.h Sources/SSLSender.cpp Headers/SSLSender.h
        Sources/SSLReceiver.cpp Headers/SSLReceiver.h Sources/IReceiver.cpp Headers/IReceiver.h
        Sources/ISender.cpp Headers/ISender.h Sources/EchoListenerSSL.cpp Headers/EchoListenerSSL.h Sources/IClientHandler.cpp Headers/IClientHandler.h Sources/ClientHandlerEcho.cpp Headers/ClientHandlerEcho.h Sources/MultiListenerSSL.cpp Headers/MultiListenerSSL.h Sources/ClientHandlerMulti.cpp Headers/ClientHandlerMulti.h Sources/ChatLogger.cpp Headers/ChatLogger.h)

find_package(OpenSSL REQUIRED)

target_link_libraries(Inheritance_Server_attempt_1 ${OPENSSL_LIBRARIES} ws2_32)

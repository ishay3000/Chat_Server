//
// Created by Ishay Cena on 05/08/2018.
//

#include <fstream>
#include <mutex>
#include "../Headers/ChatLogger.h"
#include "../includes/Data.h"
#include "../includes/mingw.mutex.h"

ChatLogger::ChatLogger() {
//    m_stream.open("Log.txt", std::ios_base::app);
}

ChatLogger::~ChatLogger() {
    if  (m_stream.is_open()){
        m_stream.close();
    }
}

static std::mutex mutex;
void ChatLogger::log(Message &message, LOG_MESSAGE messageType) {
    std::unique_lock<std::mutex> lock(mutex);
    char buffer[1024] = {0};
    char *ptrBuffer = nullptr;
    struct tm *sTime;
    time_t timeNow = time(nullptr);

    // get the time
    sTime = localtime(&timeNow);
    strftime(buffer, sizeof(buffer), "[%Y-%m-%d.%X]\t", sTime);
    ptrBuffer = buffer + strlen(buffer);
    *ptrBuffer = '\t'; // insert whitespace

    switch (messageType){
        case LOGIN:
            snprintf(ptrBuffer, 1024, "[%s] CONNECTED\n", message.header.source);
            break;
        case LOGOUT:
            snprintf(ptrBuffer, 1024, "[%s] DISCONNECTED\n", message.header.source);
            break;
        case NORMAL:
            snprintf(ptrBuffer, 1024, "[%s]\t[%s]\t[%s]\n",
                     message.header.source, message.header.destination, message.packet.dataBuffer);
            break;
    }
    if (!m_stream.is_open()) {
        m_stream.open("Chat_Log.txt", std::ios_base::app);
        m_stream << buffer;
        m_stream.close();
    }
}

void ChatLogger::Log(Message &message, LOG_MESSAGE messageType) {
    static ChatLogger m_instance;
    m_instance.log(message, messageType);
}

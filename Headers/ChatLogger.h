//
// Created by Ishay Cena on 05/08/2018.
//

#ifndef INHERITANCE_SERVER_ATTEMPT_1_CHATLOGGER_H
#define INHERITANCE_SERVER_ATTEMPT_1_CHATLOGGER_H


#include "../includes/Data.h"
#include <fstream>
#include <time.h>

typedef enum LOG_MESSAGE{
    NORMAL, LOGIN, LOGOUT
}LOG_MESSAGE;

class ChatLogger {
public:

    /**
     * writes a message to the log file
     * @param message the message to write
     * @param messageType the type of message (normal, connect or disconnect)
     */
    static void Log(Message &message, LOG_MESSAGE messageType = NORMAL);

private:
    ChatLogger();
    ~ChatLogger();
    std::ofstream m_stream;

    /**
     * writes a message to the log file
     * @param message the message to write
     * @param messageType the type of message (normal, connect or disconnect)
     */
    void log(Message &message, LOG_MESSAGE messageType);
};


#endif //INHERITANCE_SERVER_ATTEMPT_1_CHATLOGGER_H

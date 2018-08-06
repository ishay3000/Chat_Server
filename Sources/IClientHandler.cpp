//
// Created by Ishay Cena on 30/07/2018.
//

#include "../Headers/IClientHandler.h"

IClientHandler::IClientHandler(SSLSender &sender, SSLReceiver &receiver) : m_sender(sender), m_receiver(receiver){

}

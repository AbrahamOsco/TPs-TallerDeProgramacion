//
// Created by abraham on 09/10/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLSERVER_H
#define THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLSERVER_H

#include <iostream>

#include "common_actionDTO.h"
#include "common_answerDTO.h"
#include "common_protocol.h"
#include "common_socket.h"

class ServerProtocol: public Protocol {
public:
    //  Constructor del protocolo del server
    explicit ServerProtocol(Socket& socket);

    //  Pre: Socket inicializado, una accion tuvo que ser enviada antes.
    //  Post: Recibe los bytes que componene la accion y retorna un objeto ActionDTO con los valores
    //  cargados.
    ActionDTO recvAction();

    //  Pre: Socket inicializado.
    //  Post: Envia la AnswerDTO recibida como argumento.
    void sendAnswer(const AnswerDTO& aAnswer);

    //  Destructor del protocolo del server
    ~ServerProtocol() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLSERVER_H

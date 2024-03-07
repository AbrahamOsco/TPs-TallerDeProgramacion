//
// Created by abraham on 09/10/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLCLIENT_H
#define THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLCLIENT_H
#include "common_actionDTO.h"
#include "common_answerDTO.h"
#include "common_protocol.h"
#include "common_socket.h"

class ClientProtocol: public Protocol {

public:
    //  Constructor del protocolo del cliente.
    explicit ClientProtocol(Socket& socket);

    //  Pre: Socket inicializado
    //  Post: Envia la accion recibida como argumento.
    void sendAction(const ActionDTO& anAction);


    //  Pre: Socket inicializado, una accion tuvo que ser enviada antes.
    //  Post: Recibe los bytes que componene la respuesta y retorna un objeto respuestaDTO con los
    //  valores cargados.
    AnswerDTO recvAnswer();

    // Destructor del protocolo del cliente
    ~ClientProtocol() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOLCLIENT_H

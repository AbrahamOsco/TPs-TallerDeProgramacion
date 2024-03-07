//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_SERVER_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_SERVER_H

#include <string>

#include "common_answerDTO.h"
#include "common_serverProtocol.h"
#include "common_socket.h"


class Server {
private:
    Socket aceptador;  // cppcheck-suppress unusedStructMember

    //  Pre: -
    //  Post: Ejecuta el servidor con la capacidad de un solo cliente, para fines pedagogicos..
    void runSingleThread();

    //  Pre: Recibir la cantidad de jugadores actuales.
    //  Post: Printea la cantidad de jugadres actuales, en el formato especificado..
    void printNumberOfPlayers(const unsigned int& numberOfPlayers);

    //  Pre: Protocolo inicializado y recibir la cantidad de jugadores.
    //  Post: Envia al protocolo un mensaje con el estado de la partida
    void sendStatusGame(ServerProtocol& protocol, const unsigned int& numberOfPlayers);

    //  Pre: Protocolo inicializado y recibir el mensaje a enviar.
    //  Post: Envia al protocolo el mensaje que se recibe por argumento.
    void sendChatMessage(ServerProtocol& protocol, const std::string& message);

public:
    //  Constructor del server recibe el serviceName (Puerto).
    explicit Server(const char* serviceName);

    //  Pre: -
    //  Post: Ejecuta el servidor con la capacidad de acepntar n clientes, retorna 0 Si termina con
    //  exito, 1 sino.
    int run();

    //  Destructor
    ~Server() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_SERVER_H

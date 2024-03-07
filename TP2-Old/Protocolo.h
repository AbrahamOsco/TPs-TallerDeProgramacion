//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_PROTOCOLO_H
#define THREADS_PROTOCOLO_H


#include <string>
#include "Socket.h"

class Protocolo {
private:
    bool wasClosed;

public:

    bool elSocketEstaCerrado();

    Protocolo();

    void enviarCadena(Socket &socket, const std::string &unaCadena);


    std::string recibirCadena(Socket &socket);


    void recibirPeticionCrearPartida(Socket &socket, std::string& nombrePartida, std::string& cantJugReq);

    void enviarPeticionCrearPartida(Socket &socket, const std::string &nombrePartida, const std::string &cantJugReq);

    void enviarPeticionUnirsePartida(Socket &socket, const std::string &unNombrePartida);

    void recibirPeticionUnirsePartida(Socket &socket, std::string &unNombrePartida);

    void enviarResultado(Socket &socket, const bool &resultadoPeticion);

    std::string recibirResultado(Socket &socket);
};


#endif //THREADS_PROTOCOLO_H

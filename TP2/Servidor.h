//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_SERVIDOR_H
#define THREADS_SERVIDOR_H


#include "Socket.h"
#include "Protocolo.h"
#include "Juego.h"

class Servidor {
    Socket socket;
    Juego juego;

public:
    Servidor(const char *serviceName);

    int run();

    std::string recibirComando(Socket &socket, Protocolo &protocolo);

    void operacionCrear(Socket &socket, Protocolo &protocolo);

    void operacionUnir(Socket &socket, Protocolo &protocolo);

    void operacionListar(Socket &socket, Protocolo &protocolo);
};


#endif //THREADS_SERVIDOR_H

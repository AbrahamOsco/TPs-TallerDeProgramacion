//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_SERVIDOR_H
#define THREADS_SERVIDOR_H


#include "Socket.h"
#include "Protocolo.h"
#include "Juego.h"
#include "ThreadAceptador.h"
#include "JuegoProtected.h"

class Servidor {
    JuegoProtected unJuego;
    ThreadAceptador threadAceptador;

public:
    Servidor(const char *serviceName);

    int run();
};


#endif //THREADS_SERVIDOR_H

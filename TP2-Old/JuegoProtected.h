//
// Created by abraham on 24/07/23.
//

#ifndef THREADS_JUEGOPROTECTED_H
#define THREADS_JUEGOPROTECTED_H


#include <mutex>
#include "Juego.h"

class JuegoProtected {
private:
    Juego unJuego;
    std::mutex mtx;

public:
    JuegoProtected();

    bool crearPartida(std::string nombrePartida, int cantJugReq);

    bool unirsePartida(std::string nombrePartida);

    std::string listarPartidas();

};


#endif //THREADS_JUEGOPROTECTED_H

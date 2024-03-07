//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_JUEGO_H
#define THREADS_JUEGO_H


#include <map>
#include "Partida.h"

class Juego {
private:
    std::map<std::string, Partida> diccionarioPartidas;

public:
    bool crearPartida(std::string nombrePartida, int cantJugReq);

    bool unirsePartida(std::string nombrePartida);

    std::string listarPartidas();
};


#endif //THREADS_JUEGO_H

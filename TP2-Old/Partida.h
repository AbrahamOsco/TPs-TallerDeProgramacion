//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_PARTIDA_H
#define THREADS_PARTIDA_H


#include <string>

class Partida {

private:
    unsigned int cantJugRequeridos;
    int cantJugAct;
    std::string  nombrePartida;

public:
    Partida(std::string nombrePartida, int cantJugReq);

    std::string obtenerEstado() const;

    bool unirse();

    std::string getNombre();

    Partida();

};


#endif //THREADS_PARTIDA_H

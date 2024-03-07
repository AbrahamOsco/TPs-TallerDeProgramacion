#include <iostream>
#include "Partida.h"

Partida::Partida(std::string nombrePartida, int cantJugReq) : nombrePartida(nombrePartida)
                                 , cantJugRequeridos(cantJugReq), cantJugAct(1){

}

std::string Partida::obtenerEstado() const {
    std::string estado = nombrePartida + " " + std::to_string(cantJugAct) +
                            "/" + std::to_string(cantJugRequeridos) + "\n";
    return estado;
}

bool Partida::unirse() {
    if(cantJugAct == cantJugRequeridos) return false;
    cantJugAct +=1;
    if(cantJugAct == cantJugRequeridos)
        std::cout << "Comenzando partida " + nombrePartida + "...\n" ;
    return true;
}

std::string Partida::getNombre() {
    return nombrePartida;
}

Partida::Partida() : nombrePartida(""), cantJugAct(0) , cantJugRequeridos(0) {
}



//
// Created by abraham on 24/07/23.
//

#include "JuegoProtected.h"

JuegoProtected::JuegoProtected(){}

bool JuegoProtected::crearPartida(std::string nombrePartida, int cantJugReq){
    std::unique_lock<std::mutex> lck(mtx);
    return unJuego.crearPartida(nombrePartida, cantJugReq);
}

bool JuegoProtected::unirsePartida(std::string nombrePartida) {
    std::unique_lock<std::mutex> lck(mtx);
    return unJuego.unirsePartida(nombrePartida);
}

std::string JuegoProtected::listarPartidas() {
    std::unique_lock<std::mutex> lck(mtx);
    return unJuego.listarPartidas();
}

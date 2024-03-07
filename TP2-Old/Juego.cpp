#include "Juego.h"

bool Juego::crearPartida(std::string nombrePartida, int cantJugReq) {
    if( diccionarioPartidas.count(nombrePartida) > 0 ) return false;

    for( int i = 0; i < nombrePartida.size(); i++)
        nombrePartida[i] = tolower(nombrePartida[i]);

    Partida partida(nombrePartida, cantJugReq);
    diccionarioPartidas[nombrePartida] = partida;
    return true;
}


bool Juego::unirsePartida(std::string nombrePartida) {
    if( diccionarioPartidas.count(nombrePartida) == 0 ) return false;

    for( int i = 0; i < nombrePartida.size(); i++)
        nombrePartida[i] = tolower(nombrePartida[i]);

    return diccionarioPartidas[nombrePartida].unirse();
}

std::string Juego::listarPartidas() {
    std::string listadoPartidas;

    for(const auto& elemento :diccionarioPartidas ){
        listadoPartidas += elemento.second.obtenerEstado();
    }
    return listadoPartidas;
}


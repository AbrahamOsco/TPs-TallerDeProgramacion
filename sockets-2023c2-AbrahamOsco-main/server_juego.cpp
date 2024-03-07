//
// Created by abraham on 06/09/23.
//

#include "server_juego.h"

#include <string>

Juego::Juego(const std::string& nombreArchivo): archivoEscenario(nombreArchivo) {}

bool Juego::cargarEscenario(const std::string& nombreEscenario) {
    if (!archivoEscenario.cargarEscenario(nombreEscenario)) {
        return false;
    }
    int cantFilas, cantCol;
    std::string nombreMapa;
    archivoEscenario.getFilaColYNombreMapa(cantFilas, cantCol, nombreMapa);
    this->terreno = Terreno((unsigned int)cantFilas, (unsigned int)cantCol,
                            archivoEscenario.getTableroInicial());
    this->gusano = Gusano(this->terreno.getCeldaGusano());
    return true;
}

void Juego::girarGusano(const int& direccion) {
    if (direccion == 0) {
        this->gusano.girarIzquierda();
    } else if (direccion == 1) {
        this->gusano.girarDerecha();
    }
}


void Juego::moverGusano() { this->terreno.mover(gusano); }

void Juego::saltarGusano(const int& tipoSalto) {
    if (tipoSalto == 0) {
        this->terreno.jumpAdelante(gusano);
    } else if (tipoSalto == 1) {
        this->terreno.jumpAtras(gusano);
    }
}

void Juego::getPosicionGusano(unsigned int& posFila, unsigned int& posCol) {
    gusano.getPosiciones(posFila, posCol);
}

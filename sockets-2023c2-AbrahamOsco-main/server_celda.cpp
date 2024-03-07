//
// Created by abraham on 06/09/23.
//

#include "server_celda.h"

#include <iostream>


Celda::Celda(): estadoActual(ESTADO_A_SER_DEFINIDO), simbolo("?") {}


Celda::Celda(const char& unSimbolo, Posicion unaPos):
        estadoActual(ESTADO_A_SER_DEFINIDO), posicion(unaPos) {

    this->simbolo = std::string(1, unSimbolo);
    if (this->simbolo == SIMBOLO_VIGA) {
        estadoActual = ESTADO_VIGA;
    } else if (this->simbolo == SIMBOLO_AIRE) {
        estadoActual = ESTADO_AIRE;
    } else if (this->simbolo == SIMBOLO_GUSANO) {
        estadoActual = ESTADO_CON_GUSANO;
    }
}

std::string Celda::getSimbolo() const { return simbolo; }


Posicion Celda::getPosicion() const { return posicion; }

void Celda::getPosiciones(unsigned int& posFil, unsigned int& posCol) const {
    posicion.getPosiciones(posFil, posCol);
}


bool Celda::esAvanzable() const { return this->simbolo != SIMBOLO_VIGA; }

void Celda::liberarCelda() {
    estadoActual = ESTADO_AIRE;
    this->simbolo = " ";
}

void Celda::asignarGusano() {
    estadoActual = ESTADO_CON_GUSANO;
    this->simbolo = SIMBOLO_GUSANO;
}

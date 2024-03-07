//
// Created by abraham on 06/09/23.
//

#include "server_posicion.h"

#include <iostream>

Posicion::Posicion(): posFila(0), posCol(0) {}

Posicion::Posicion(const unsigned int& unaPosFila, const unsigned int& unaPosCol):
        posFila(unaPosFila), posCol(unaPosCol) {}

Posicion Posicion::getIzq() const { return Posicion(posFila, posCol - 1); }

Posicion Posicion::getDerecha() const { return Posicion(posFila, posCol + 1); }

void Posicion::getPosiciones(unsigned int& posFila, unsigned int& posCol) const {
    posFila = this->posFila;
    posCol = this->posCol;
}

Posicion Posicion::getArriba() const { return Posicion(posFila - 1, posCol); }

Posicion Posicion::getAbajo() const { return Posicion(posFila + 1, posCol); }

//
// Created by abraham on 06/09/23.
//

#include "server_gusano.h"

#include <iostream>
#include <vector>

Gusano::Gusano(const Celda& celdaActual): celdaActual(celdaActual) { direccion = IZQUIERDA; }

Gusano::Gusano() { direccion = IZQUIERDA; }

void Gusano::girarIzquierda() { direccion = IZQUIERDA; }

void Gusano::girarDerecha() { direccion = DERECHA; }

void Gusano::proxMovimiento(unsigned int& proxPosibPosFil, unsigned int& proxPosibPosCol) const {
    Posicion posAct = celdaActual.getPosicion();
    Posicion proxPosibPos;
    if (direccion == IZQUIERDA) {
        proxPosibPos = posAct.getIzq();
    } else if (direccion == DERECHA) {
        proxPosibPos = posAct.getDerecha();
    }
    proxPosibPos.getPosiciones(proxPosibPosFil, proxPosibPosCol);
}

void Gusano::getPosiciones(unsigned int& posFila, unsigned int& posCol) const {
    celdaActual.getPosiciones(posFila, posCol);
}

void Gusano::asignarNuevaCelda(const Celda& nuevaCelda) { celdaActual = nuevaCelda; }

std::vector<Posicion> Gusano::jumpAdelante() const {
    Posicion posAct = celdaActual.getPosicion();
    Posicion arriba = posAct.getArriba();
    Posicion adelante1, adelante2;
    if (direccion == 0) {
        adelante1 = arriba.getIzq();
        adelante2 = adelante1.getIzq();
    } else if (direccion == 1) {
        adelante1 = arriba.getDerecha();
        adelante2 = adelante1.getDerecha();
    }
    std::vector<Posicion> posJumpAdelante = {arriba, adelante1, adelante2};
    return posJumpAdelante;
}

void Gusano::caer(unsigned int& proxPosFil, unsigned int& proxPosCol) const {
    Posicion posAct = celdaActual.getPosicion();
    Posicion posAbajo = posAct.getAbajo();
    posAbajo.getPosiciones(proxPosFil, proxPosCol);
}

std::vector<Posicion> Gusano::jumpAtras() const {
    Posicion posAct = celdaActual.getPosicion();
    Posicion arriba1 = posAct.getArriba();
    Posicion arriba2 = arriba1.getArriba();
    Posicion opuestaDireccion;
    if (direccion == 0) {
        opuestaDireccion = arriba2.getDerecha();
    } else if (direccion == 1) {
        opuestaDireccion = arriba2.getIzq();
    }
    std::vector<Posicion> posJumpAtras = {arriba1, arriba2, opuestaDireccion};
    return posJumpAtras;
}

//
// Created by abraham on 06/09/23.
//

#include "server_terreno.h"

#include "server_posicion.h"

Terreno::Terreno(): filas(0), columnas(0) {}

Terreno::Terreno(const unsigned int& filas, const unsigned int& columnas,
                 const std::vector<std::string>& filasMapa):
        filas(filas), columnas(columnas) {
    for (unsigned int i = 0; i < filas; i++) {
        std::vector<Celda> unasCeldas;
        std::string unaFila = filasMapa[i];
        for (unsigned int j = 0; j < columnas; j++) {
            Celda unaCelda = Celda(unaFila[j], Posicion(i, j));
            unasCeldas.push_back(unaCelda);
        }
        this->celdas.push_back(unasCeldas);
    }
}

Celda Terreno::getCeldaGusano() const {
    for (unsigned int i = 0; i < filas; i++) {
        for (unsigned int j = 0; j < columnas; j++) {
            if (celdas[i][j].getSimbolo() == "G") {
                return celdas[i][j];
            }
        }
    }
    return celdas[0][0];
}

void Terreno::mover(Gusano& gusano) {
    unsigned int proxPosFila, proxPosCol;
    gusano.proxMovimiento(proxPosFila, proxPosCol);

    if (esAvanzable(proxPosFila, proxPosCol)) {
        moverA(gusano, proxPosFila, proxPosCol);
    }
    aplicarGravedad(gusano);
}

void Terreno::moverA(Gusano& gusano, const unsigned int& proxPosFila,
                     const unsigned int& proxPosCol) {
    unsigned int posFilAntigua, posColAntigua;
    gusano.getPosiciones(posFilAntigua, posColAntigua);

    this->celdas[posFilAntigua][posColAntigua].liberarCelda();
    celdas[proxPosFila][proxPosCol].asignarGusano();
    gusano.asignarNuevaCelda(celdas[proxPosFila][proxPosCol]);
}

void Terreno::jumpAdelante(Gusano& gusano) {
    std::vector<Posicion> unasPosiciones = gusano.jumpAdelante();
    jumpGenerico(gusano, unasPosiciones);
}

void Terreno::aplicarGravedad(Gusano& gusano) {
    unsigned int proxPosFila, proxPosCol;
    gusano.caer(proxPosFila, proxPosCol);
    while (esAvanzable(proxPosFila, proxPosCol)) {
        moverA(gusano, proxPosFila, proxPosCol);
        gusano.caer(proxPosFila, proxPosCol);
    }
}

void Terreno::jumpGenerico(Gusano& gusano, const std::vector<Posicion>& posicionesSalto) {
    unsigned int proxPosFil, proxPosCol;
    for (auto item: posicionesSalto) {
        item.getPosiciones(proxPosFil, proxPosCol);
        if (esAvanzable(proxPosFil, proxPosCol)) {
            moverA(gusano, proxPosFil, proxPosCol);
        } else {
            break;
        }
    }
    aplicarGravedad(gusano);
}

bool Terreno::esAvanzable(unsigned int const& proxPosFila, unsigned int const& proxPosCol) {
    return (proxPosFila < filas && proxPosCol < columnas &&
            this->celdas[proxPosFila][proxPosCol].esAvanzable());
}

void Terreno::jumpAtras(Gusano& gusano) {
    std::vector<Posicion> unasPosiciones = gusano.jumpAtras();
    jumpGenerico(gusano, unasPosiciones);
}

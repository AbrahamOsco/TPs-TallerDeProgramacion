//
// Created by abraham on 06/09/23.
//

#ifndef SOCKETS_2023C2_ABRAHAMOSCO_TERRENO_H
#define SOCKETS_2023C2_ABRAHAMOSCO_TERRENO_H

#include <iostream>
#include <string>
#include <vector>

#include "server_celda.h"
#include "server_gusano.h"

class Terreno {

private:
    std::vector<std::vector<Celda>> celdas;  // cppcheck-suppress unusedStructMember

    unsigned int filas;  // cppcheck-suppress unusedStructMember

    unsigned int columnas;  // cppcheck-suppress unusedStructMember


    //  Pre: Una referencia del gusano y las proxima filas y columa donde queremos que esteè el
    //  gusano. Post: Se mueve al gusano a la proxima fila y columna recibida como argumento.
    void moverA(Gusano& gusano, const unsigned int& proxPosFila, const unsigned int& proxPosCol);

    //  Pre: Una referencia al gusano y las posiciones del salto a realizar.
    //  Post: Se movera el gusano a cada poscion indicada por argumento (si se puede)
    void jumpGenerico(Gusano& gusano, const std::vector<Posicion>& posicionesSalto);

    //  Pre: recibir la proxima fila y columna a mover al gusano.
    //  Post: Retorna true si la fila y columna son menores que las dimensiones del tablero y no
    //  estan en una celda con viga.
    bool esAvanzable(const unsigned int& proxPosFila, const unsigned int& proxPosCol);

    //  Pre: -.
    //  Post: Aplicara la gravedad al gusano si esta en una celda con simbolo aire bajara hasta
    //  "chocar" con el suelo..
    void aplicarGravedad(Gusano& gusano);

public:
    //  Constructor del Terreno
    //  Pre: Recibe la cantidad de filas, columnas y el tablero de strings.
    //  Post: Retorna un tablero en estado consistente.
    Terreno(const unsigned int& filas, const unsigned int& columnas,
            const std::vector<std::string>& mapaString);

    //  Constructor del Terreno default
    //  Pre: -.
    //  Post: Retorna un Terreno con solo la fila y columna seteada en cero.
    Terreno();

    //  Pre: Terreno en estado consistente
    //  Post: Devolvemos la celda donde se encuentra el gusano actualmente en el tablero.
    Celda getCeldaGusano() const;

    //  Pre: Terreno en estado consistente
    //  Post: EL gusano se mueve (si se puede) segun la direccion definida apriori, se aplica la
    //  gravedad al finalizar.
    void mover(Gusano& gusano);

    //  Pre: Terreno en estado consistente
    //  Post: El gusano realiza el jump adelante (si no choca con una viga), se aplica la gravedad
    //  al finalizar.
    void jumpAdelante(Gusano& gusano);

    //  Pre: Terreno en estado consistente
    //  Post: El gusano realiza el jump atras (si no choca con una viga), se aplica la gravedad al
    //  finalizar.
    void jumpAtras(Gusano& gusano);

    //  Destructor
    ~Terreno() = default;
};


#endif  // SOCKETS_2023C2_ABRAHAMOSCO_TERRENO_H

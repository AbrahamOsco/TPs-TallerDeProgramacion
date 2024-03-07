//
// Created by abraham on 06/09/23.
//

#ifndef SOCKETS_2023C2_ABRAHAMOSCO_CELDA_H
#define SOCKETS_2023C2_ABRAHAMOSCO_CELDA_H

#include <string>

#include "server_posicion.h"
#define SIMBOLO_AIRE "A"
#define SIMBOLO_GUSANO "G"
#define SIMBOLO_VIGA "X"

enum EstadoCelda { ESTADO_A_SER_DEFINIDO, ESTADO_AIRE, ESTADO_VIGA, ESTADO_CON_GUSANO };

class Celda {

private:
    EstadoCelda estadoActual;  // cppcheck-suppress unusedStructMember
    std::string simbolo;       // cppcheck-suppress unusedStructMember
    Posicion posicion;         // cppcheck-suppress unusedStructMember

public:
    //  Constructor de la clase Celda
    //  Pre: Recibe el simbolo de la celda y la posicion donde se ubica la celda.
    //  Post: Retorna una celda en un estado consistente.
    Celda(const char& unSimbolo, Posicion posicion);

    //  Consturctor por defecto.
    //  Pre: -
    //  Post: Retorna una celda en estado por definir.
    Celda();

    //  Pre: -
    //  Post: Retorna el simbolo definido en la celda.
    std::string getSimbolo() const;

    //  Pre: Celda en un estado consistente,
    //  Post: obtiene la posicion asociada a esa celda.
    Posicion getPosicion() const;

    //  Pre: Celda en un estado consistente,
    //  Post: retorna si la celda puede ser avanzable por un gusano o no (es decir si no es una
    //  viga).
    bool esAvanzable() const;

    //  Pre: Celda en un estado consistente,
    //  Post: Asigna a la celda el simbolo de "AIRE".
    void liberarCelda();

    //  Pre: Celda en un estado consistente,
    //  Post: Asigna a la celda el simbolo de "GUSANO", para indicar que el gusano se situa ahi
    //  actualmente.
    void asignarGusano();

    //  Pre: Celda en un estado consistente,
    //  Post: asigna a las posFila y posCol recibida como argumentos la fila y columna actual donde
    //  se encuentra la celda
    void getPosiciones(unsigned int& posFil, unsigned int& posCol) const;

    //  Destructor de la clase Celda.
    ~Celda() = default;
};


#endif  // SOCKETS_2023C2_ABRAHAMOSCO_CELDA_H

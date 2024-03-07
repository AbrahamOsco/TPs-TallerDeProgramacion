//
// Created by abraham on 06/09/23.
//

#ifndef TP1_SOCKET_DB_GUSANO_H
#define TP1_SOCKET_DB_GUSANO_H


#include <string>
#include <vector>

#include "server_celda.h"
#define IZQUIERDA 0
#define DERECHA 1

class Gusano {
private:
    Celda celdaActual;  // cppcheck-suppress unusedStructMember
    int direccion;      // cppcheck-suppress unusedStructMember

public:
    //  Constructor del gusano
    //  Pre: Recibe la celda actual donde debe estar ubicado,
    //  Post: Se obtiene un gusano en un estado consistente.
    explicit Gusano(const Celda& celdaActual);

    //  Constructor del gusano por default
    //  Pre: -.
    //  Post: Se obtiene un gusano en un estado a definir (falta asignar la celda actual).
    Gusano();

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: EL gusano tendra como direccion la izquierda .
    void girarIzquierda();

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: EL gusano tendra como direccion la derecha .
    void girarDerecha();

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: obtiene la proxima fila y columna resultado de mover el gusano (No se toma en cuenta
    //  la gravedad ni las vigas) asigna el valor a su argumento asociado respectivamente.
    void proxMovimiento(unsigned int& proxPosibPosFil, unsigned int& proxPosibPosCol) const;

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: obtiene las fila y columna actual del gusano y lo asigna al argumento asociado
    //  respectivamente.
    void getPosiciones(unsigned int& posFila, unsigned int& posCol) const;

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: actualiza la celda actual del gusano por la nueva celda recibida por argumento.
    void asignarNuevaCelda(const Celda& nuevaCelda);

    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: Devuelve un vector con las 3 posiciones asociadas al jump adelante.
    std::vector<Posicion> jumpAdelante() const;


    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: Devuelve un vector con las 3 posiciones asociadas al jump atras.
    std::vector<Posicion> jumpAtras() const;


    //  Pre: Gusano debe estar en un estado consistente.
    //  Post: obtiene la fila y columna que estan por debajo de la posicion actual del gusano y
    //  asigna los valores a su argumento asociado respectivamente.
    void caer(unsigned int& proxPosFil, unsigned int& proxPosCol) const;

    //  Destructor
    ~Gusano() = default;
};


#endif  // TP1_SOCKET_DB_GUSANO_H

//
// Created by abraham on 06/09/23.
//

#ifndef TP1_SOCKET_DB_POSICION_H
#define TP1_SOCKET_DB_POSICION_H


class Posicion {
private:
    unsigned int posFila;  // cppcheck-suppress unusedStructMember
    unsigned int posCol;   // cppcheck-suppress unusedStructMember

public:
    //  Constructor de la clase Posicion
    //  Pre: recibe la fila y la columna a asignar para la posicion
    //  Post: Retorna una posicione en estado consistente.
    Posicion(const unsigned int& unaPosFila, const unsigned int& unaPosCol);

    //  Constructor por default de la clase Posicion
    //  Pre: -
    //  Post: Retorna una posicion con fila y columan seteadas en cero.
    Posicion();

    //  Pre: Tener la posicion en un estado consistente
    //  Post: Retorna la posicion izquierda de la posicion actual.
    Posicion getIzq() const;

    //  Pre: Tener la posicion en un estado consistente
    //  Post: Retorna la posicion derecha de la posicion actual.
    Posicion getDerecha() const;

    //  Pre: Tener la posicion en un estado consistente
    //  Post: Retorna la posicion derecha de la posicion actual.
    Posicion getArriba() const;

    //  Pre: Tener la posicion en un estado consistente
    //  Post: Retorna la posicion inferior de la posicion actual.
    Posicion getAbajo() const;

    //  Pre: Tener la posicion en un estado consistente
    //  Post: obtiene la fila y columa y las asigna segun el argumento asociado respectivamente.
    void getPosiciones(unsigned int& posFila, unsigned int& posCol) const;

    //  Destructor
    ~Posicion() = default;
};


#endif  // TP1_SOCKET_DB_POSICION_H

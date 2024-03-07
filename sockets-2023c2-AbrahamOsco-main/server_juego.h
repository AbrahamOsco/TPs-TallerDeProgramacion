//
// Created by abraham on 06/09/23.
//

#ifndef TP1_SOCKET_DB_JUEGO_H
#define TP1_SOCKET_DB_JUEGO_H


#include <string>

#include "server_archivoEscenario.h"
#include "server_gusano.h"
#include "server_terreno.h"

class Juego {
private:
    ArchivoEscenario archivoEscenario;  // cppcheck-suppress unusedStructMember
    Terreno terreno;                    // cppcheck-suppress unusedStructMember
    Gusano gusano;                      // cppcheck-suppress unusedStructMember

public:
    //  Constructor del Juego
    //  Pre: Recibir el nombre del archivo para poder obtener los escenarios.
    //  Post: Se obtiene el juego con el terreno y gusano pendientes a definir.
    explicit Juego(const std::string& nombreArchivo);

    //  Pre: Haber definido el gusano, recibe la direccion a mover el gusano.
    //  Post: el gusano actualizara su direcicon a la indicada.
    void girarGusano(const int& direccion);

    //  Pre: Haber definido el gusano.
    //  Post: Mueve el gusano en una celda segun la direccion apriori definida .
    void moverGusano();

    //  Pre: Recibe el nombre del escenario para poder definir el terreno y el gusano
    //  Post: Se Definen el gusano y el terreno obteniendo el juego en un estado consistente.
    bool cargarEscenario(const std::string& nombreEscenario);

    //  Pre: Haber definido el gusano.
    //  Post: Se obtienen las posiciones de la fila y columna actual del gusano y se las asigna
    //  a los argumentos asociados respectivamente.
    void getPosicionGusano(unsigned int& posFila, unsigned int& posCol);

    //  Pre: Haber definido el gusano.
    //  Post: el gusano realizara el salto segun el tipo de salto indicada (1:Jump atras, 0: Jump
    //  adelante)
    void saltarGusano(const int& tipoSalto);

    //  Destructor
    ~Juego() = default;
};


#endif  // TP1_SOCKET_DB_JUEGO_H

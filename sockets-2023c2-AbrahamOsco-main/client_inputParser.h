//
// Created by abraham on 18/09/23.
//

#ifndef SOCKETS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H
#define SOCKETS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H

#include <iostream>
#include <sstream>
#include <string>

#include "common_operacionDTO.h"

class InputParser {
private:
    std::string comandoActual;    // cppcheck-suppress unusedStructMember
    std::string operacionActual;  // cppcheck-suppress unusedStructMember
    std::string nombreEscenario;  // cppcheck-suppress unusedStructMember
    Operacion operacionNum;       // cppcheck-suppress unusedStructMember
    Direccion direccion;          // cppcheck-suppress unusedStructMember
    TipoSalto salto;              // cppcheck-suppress unusedStructMember


public:
    //  Constructor del objeto InputParser
    explicit InputParser(const std::string& unComando);

    //  Pre: -
    //  Pos: retorna true si encuentra una linea vacia o le llego al fin de archivo, sino retorna
    //  false.
    bool seDetuvo();

    //  Pre: -
    //  Pos: retorna true si encuentra un simbolo '#' o una linea vacia, sino retorna false
    bool esIgnorable();

    //  Pre: -
    //  Pos: parsea el input del usuario rellenando los valores recibidos en los atributos,
    void parsear();

    //  Pre: haber parseado anteriormente el input del usuario.
    //  Pos: Devuelve un objeto OperacionDTO con los valores del comando ya parseados.
    OperacionDTO getOperacionDTO();
};


#endif  // SOCKETS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H

//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H
#define THREADS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H

#include <iostream>
#include <string>

#include "common_actionDTO.h"

class InputParser {
private:
    std::string accionAct;   // cppcheck-suppress unusedStructMember
    std::string mensaje;     // cppcheck-suppress unusedStructMember
    unsigned int cantReads;  // cppcheck-suppress unusedStructMember

public:
    //  Constructor del inputParser
    InputParser();

    //  Pre:  -
    //  Post:Parsea el input ingresado tomando en cuenta la primera palabra ingresada y lo guarda.
    void parse();

    //  Pre:  -
    //  Post: Reinicia los atributos, retorna True si la primera ingresada es distinta a Exit, false
    //  en caso opuesto.
    bool keepParsing();

    //  Pre:  Haber parseado anteriormente
    //  Post: Retorna una AccionDTO, encapsulando el tipo de accion y su respectivos valores
    //  asociado.
    ActionDTO getAction() const;

    //  Destructor
    ~InputParser() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_CLIENT_INPUTPARSER_H

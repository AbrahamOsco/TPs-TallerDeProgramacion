//
// Created by abraham on 27/09/23.
//

#include "client_inputParser.h"

#include <iostream>

InputParser::InputParser(): accionAct(""), cantReads(0) {}

bool InputParser::keepParsing() {
    accionAct = mensaje = "";
    cantReads = 0;
    std::cin >> accionAct;
    return accionAct != ACCION_EXIT;
}

void InputParser::parse() {
    if (accionAct == ACCION_CHAT) {
        std::cin >> std::ws;
        std::getline(std::cin, mensaje, '\n');
    } else if (accionAct == ACCION_READ) {
        std::cin >> cantReads;
    }
}

ActionDTO InputParser::getAction() const {
    ActionDTO unaAccion;
    unaAccion.setActionAct(accionAct);
    if (accionAct == ACCION_CHAT) {
        unaAccion.setMessage(mensaje);
    } else if (accionAct == ACCION_READ) {
        unaAccion.setNumberOfReads(cantReads);
    }
    return unaAccion;
}

//
// Created by abraham on 27/09/23.
//

#include "common_actionDTO.h"

#include <iostream>

ActionDTO::ActionDTO(): accionAct(""), cantReads(0) {}

void ActionDTO::setActionAct(const std::string& anAction) { this->accionAct = anAction; }

void ActionDTO::setNumberOfReads(const unsigned int& aMessage) { this->cantReads = aMessage; }

void ActionDTO::setMessage(const std::string& aMessage) { this->mensaje = aMessage; }

std::string ActionDTO::getActionAct() const { return accionAct; }

std::string ActionDTO::getMessage() const {
    if (accionAct != ACCION_CHAT) {
        throw std::runtime_error(
                "Error no se puede obtener el mensaje para una accion distinta de Chat\n");
    }
    return mensaje;
}

unsigned int ActionDTO::getNumberOfReads() const {
    if (accionAct != ACCION_READ) {
        throw std::runtime_error("Error no se puede obtener la cantidad de reads para una accion "
                                 "distinta de Read\n");
    }
    return cantReads;
}

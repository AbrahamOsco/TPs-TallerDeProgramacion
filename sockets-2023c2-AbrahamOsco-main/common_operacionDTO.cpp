//
// Created by abraham on 18/09/23.
//

#include "common_operacionDTO.h"

OperacionDTO::OperacionDTO():
        operacionNumerica(Operacion::EXIT),
        nombreEscenario(""),
        direccion(Direccion::IZQUIERDA),
        salto(TipoSalto::ADELANTE) {}

void OperacionDTO::setNombreEscenario(const std::string& unNombreEscenario) {
    this->nombreEscenario = unNombreEscenario;
}

void OperacionDTO::setDireccion(const Direccion& unaDireccion) { this->direccion = unaDireccion; }

void OperacionDTO::setSalto(const TipoSalto& unSalto) { this->salto = unSalto; }

void OperacionDTO::setTipo(const Operacion& unaOperacion) {
    this->operacionNumerica = unaOperacion;
}

std::string OperacionDTO::getNombreEscenario() const {
    if (this->operacionNumerica != Operacion::SELECT)
        throw std::runtime_error("Error no se puede pedir el nombre del escenario para una "
                                 "operacion que no sea Select\n");
    return nombreEscenario;
}

Direccion OperacionDTO::getDireccion() const {
    if (this->operacionNumerica != Operacion::DIRECCION)
        throw std::runtime_error(
                "Error no se puede pedir la direccion para una operacion que no sea DIR\n");
    return direccion;
}

TipoSalto OperacionDTO::getSalto() const {
    if (this->operacionNumerica != Operacion::JUMP)
        throw std::runtime_error(
                "Error no se puede pedir el tipo de salto para una operacion que no sea JUMP\n");

    return salto;
}

Operacion OperacionDTO::getTipo() const { return operacionNumerica; }

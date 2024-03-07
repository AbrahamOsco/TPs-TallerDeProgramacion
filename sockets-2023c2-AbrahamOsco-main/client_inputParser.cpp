//
// Created by abraham on 18/09/23.
//

#include "client_inputParser.h"
InputParser::InputParser(const std::string& unComando):
        comandoActual(unComando),
        operacionActual(""),
        nombreEscenario(""),
        operacionNum(Operacion::EXIT),
        direccion(Direccion::IZQUIERDA),
        salto(TipoSalto::ADELANTE) {}

bool InputParser::seDetuvo() { return (std::cin.eof() || comandoActual == ""); }


void InputParser::parsear() {
    std::istringstream inputParaParseo(comandoActual);
    inputParaParseo >> operacionActual;
    int unaDireccion, unSalto;
    if (operacionActual == "select") {
        inputParaParseo >> nombreEscenario;
        operacionNum = Operacion::SELECT;
    } else if (operacionActual == "dir") {
        inputParaParseo >> unaDireccion;
        operacionNum = Operacion::DIRECCION;
        (unaDireccion == IZQUIERDA) ? direccion = Direccion::IZQUIERDA :
                                      direccion = Direccion::DERECHA;
    } else if (operacionActual == "jump") {
        operacionNum = Operacion::JUMP;
        inputParaParseo >> unSalto;
        (unSalto == ADELANTE) ? salto = TipoSalto::ADELANTE : salto = TipoSalto::ATRAS;
    } else if (operacionActual == "move") {
        operacionNum = Operacion::MOVER;
    }
}

OperacionDTO InputParser::getOperacionDTO() {
    OperacionDTO unaOperacion;
    unaOperacion.setNombreEscenario(nombreEscenario);
    unaOperacion.setSalto(salto);
    unaOperacion.setDireccion(direccion);
    unaOperacion.setTipo(operacionNum);
    return unaOperacion;
}

bool InputParser::esIgnorable() { return (operacionActual == "#" || operacionActual.empty()); }

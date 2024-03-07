//
// Created by abraham on 08/09/23.
//

#include "client_cliente.h"

#include <iostream>
#include <sstream>
#include <string>

#include "client_inputParser.h"
#include "common_protocolo.h"

Cliente::Cliente(const char* hostName, const char* serviceName):
        sktCliente(hostName, serviceName) {}

int Cliente::run() {
    Protocolo protocolo(std::move(sktCliente));
    realizarOperaciones(protocolo);
    return 0;
}

void Cliente::realizarOperaciones(Protocolo& protocolo) {
    std::string inputUsuario;
    while (std::getline(std::cin, inputUsuario, '\n')) {
        InputParser unInputParser(inputUsuario);
        if (unInputParser.seDetuvo())
            break;
        unInputParser.parsear();
        if (unInputParser.esIgnorable())
            continue;
        OperacionDTO unaOperacion = unInputParser.getOperacionDTO();
        protocolo.enviarOperacionDTO(unaOperacion);
        if (unaOperacion.getTipo() == Operacion::SELECT) {
            imprimirRsptEscenario(protocolo.recibirRsptEscenarioDTO());
        } else {
            imprimirPosicionesGusano(protocolo.recibirRsptDTO());
        }
    }
}

void Cliente::imprimirPosicionesGusano(const RespuestaDTO& unaRsptDTO) {
    std::cout << unaRsptDTO.getPosCol() << " " << unaRsptDTO.getPosFila() << "\n";
}

void Cliente::imprimirRsptEscenario(const RespuestaDTO& rsptDTO) {
    if (rsptDTO.getRespuesta() == Respuesta::ERROR) {
        throw std::runtime_error("Error no se encontro el nombre del escenario ingresado \n");
    } else {
        imprimirPosicionesGusano(rsptDTO);
    }
}

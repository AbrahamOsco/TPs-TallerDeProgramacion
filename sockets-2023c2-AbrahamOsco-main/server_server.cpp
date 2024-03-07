//
// Created by abraham on 07/09/23.
//

#include "server_server.h"

#include <string>

#include "common_protocolo.h"
#include "common_respuestaDTO.h"

Server::Server(const char* serviceName, const char* nombreArchivo):
        aceptador(serviceName), juego(nombreArchivo) {}


int Server::run() {
    Socket peer = aceptador.accept();
    Protocolo protocolo(std::move(peer));
    realizarOperaciones(protocolo);
    return 0;
}

void Server::realizarOperaciones(Protocolo& protocolo) {
    while (protocolo.estaDisponible()) {
        OperacionDTO operacionDto = protocolo.recibirOperacionDTO();
        Operacion tipo = operacionDto.getTipo();
        if (tipo == Operacion::SELECT) {
            seleccionarEscenario(protocolo, operacionDto.getNombreEscenario());
        } else if (tipo == Operacion::DIRECCION) {
            girarAlGusano(protocolo, operacionDto.getDireccion());
        } else if (tipo == Operacion::MOVER) {
            moverAlGusano(protocolo);
        } else if (tipo == Operacion::JUMP) {
            saltarGusano(protocolo, operacionDto.getSalto());
        } else {
            break;
        }
    }
}

void Server::seleccionarEscenario(Protocolo& protocolo, const std::string& nombreEscenario) {
    RespuestaDTO respuesta;
    if (juego.cargarEscenario(nombreEscenario)) {
        respuesta.setEstado(Respuesta::EXITO);
        unsigned int posFila, posCol;
        juego.getPosicionGusano(posFila, posCol);
        respuesta.setPosiciones(posFila, posCol);
        std::cout << posCol << " " << posFila << "\n";
    } else {
        respuesta.setEstado(Respuesta::ERROR);
    }
    protocolo.enviarRespuestaDTO(respuesta);
}

void Server::girarAlGusano(Protocolo& protocolo, const Direccion& direccion) {
    juego.girarGusano(direccion);
    enviarPosicionesDelGusano(protocolo);
}

void Server::moverAlGusano(Protocolo& protocolo) {
    juego.moverGusano();
    enviarPosicionesDelGusano(protocolo);
}

void Server::saltarGusano(Protocolo& protocolo, const TipoSalto& salto) {
    juego.saltarGusano(salto);
    enviarPosicionesDelGusano(protocolo);
}

void Server::enviarPosicionesDelGusano(Protocolo& protocolo) {
    RespuestaDTO rsptDTO;
    unsigned int posFila, posCol;
    juego.getPosicionGusano(posFila, posCol);
    rsptDTO.setPosiciones(posFila, posCol);
    protocolo.enviarRespuestaDTO(rsptDTO);
    std::cout << posCol << " " << posFila << "\n";
}

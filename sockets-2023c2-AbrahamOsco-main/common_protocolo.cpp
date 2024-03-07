//
// Created by abraham on 07/09/23.
//

#include "common_protocolo.h"

#include <iostream>
#include <string>
#include <vector>

#include <netinet/in.h>

Protocolo::Protocolo(Socket unSktPeer): peer(std::move(unSktPeer)) { estaCerrado = false; }


bool Protocolo::estaDisponible() const { return !estaCerrado; }

void Protocolo::enviarCreacionEscenario(const std::string& nombreEscenario) {
    enviarOperacion(Operacion::SELECT);
    uint16_t tamanioNombreEscenario = nombreEscenario.size();
    tamanioNombreEscenario = htons(tamanioNombreEscenario);

    size_t s = 0;
    s += peer.sendall(&tamanioNombreEscenario, sizeof(tamanioNombreEscenario), &estaCerrado);
    s += peer.sendall(nombreEscenario.data(), nombreEscenario.size(),
                      &estaCerrado);  //  size no incluye '\0'
    if (s != (sizeof(tamanioNombreEscenario) + nombreEscenario.size())) {
        throw std::runtime_error("Error en el enviarCreacionEscenario\n");
    }
}

void Protocolo::recibirCreacionEscenario(std::string& nombreEscenario) {
    uint16_t tamanioNombre = 0;
    size_t s = 0;

    s += peer.recvall(&tamanioNombre, sizeof(tamanioNombre), &estaCerrado);
    tamanioNombre = ntohs(tamanioNombre);
    int tamanioBuffer = (int)tamanioNombre;
    std::vector<char> buffer(tamanioBuffer);
    s += peer.recvall(buffer.data(), tamanioBuffer, &estaCerrado);
    if (s != sizeof(uint16_t) + (tamanioBuffer)) {
        throw std::runtime_error("Error en el recibirCreacionEscenario\n");
    }
    nombreEscenario = std::string(buffer.begin(), buffer.end());
}


void Protocolo::enviarOperacion(const int& operacion) {
    uint8_t operacionSend = operacion;
    size_t s = 0;
    s += peer.sendall(&operacionSend, sizeof(operacionSend), &estaCerrado);
    if (s != sizeof(operacionSend)) {
        throw std::runtime_error("Error en el enviar Operacion\n");
    }
}

int Protocolo::recibirOperacion() {
    uint8_t operacionRecv;
    size_t s = 0;
    s += peer.recvall(&operacionRecv, sizeof(operacionRecv), &estaCerrado);
    if (s != sizeof(operacionRecv)) {
        return Operacion::EXIT;  //  El cliente cerro la conexion.
    }
    return int(operacionRecv);
}


void Protocolo::enviarRstpExitoCrearEscenario(const unsigned int& posFila,
                                              const unsigned int& posColumna) {
    uint8_t respuesta = Respuesta::EXITO;
    size_t s = 0;
    s += peer.sendall(&respuesta, sizeof(respuesta), &estaCerrado);
    enviarPosicionGusano(posFila, posColumna);
    if (s != sizeof(respuesta)) {
        throw std::runtime_error("Error al Enviar Rstp de Exito al Crear Escenario");
    }
}

void Protocolo::enviarRsptErrorCrearEscenario() {
    uint8_t respuesta = Respuesta::ERROR;
    size_t s = 0;
    s += peer.sendall(&respuesta, sizeof(respuesta), &estaCerrado);
    if (s != sizeof(respuesta)) {
        throw std::runtime_error("Error al enviar la Rspt Error al CrearEscenario\n");
    }
}

void Protocolo::enviarPosicionGusano(const unsigned int& posFila, const unsigned int& posColumna) {
    uint32_t posFilEnviar = posFila;
    uint32_t posColEnviar = posColumna;
    posFilEnviar = htonl(posFilEnviar);
    posColEnviar = htonl(posColEnviar);
    size_t s = 0;

    s += peer.sendall(&posColEnviar, sizeof(posColEnviar), &estaCerrado);
    s += peer.sendall(&posFilEnviar, sizeof(posFilEnviar), &estaCerrado);
    if (s != sizeof(posColEnviar) + sizeof(posFilEnviar)) {
        throw std::runtime_error("Error en Enviar la posicion del gusano \n");
    }
}

void Protocolo::recibirPosicionesGusano(unsigned int& posFila, unsigned int& posCol) {
    uint32_t posFilaRecv;
    uint32_t posColRecv;
    size_t s = 0;
    s += peer.recvall(&posColRecv, sizeof(posColRecv), &estaCerrado);
    s += peer.recvall(&posFilaRecv, sizeof(posFilaRecv), &estaCerrado);
    posFilaRecv = ntohl(posFilaRecv);
    posColRecv = ntohl(posColRecv);
    if (s != sizeof(posColRecv) + sizeof(posFilaRecv)) {
        throw std::runtime_error("Error al recibir las posiciones del gusano \n");
    }
    posFila = posFilaRecv;
    posCol = posColRecv;
}

int Protocolo::recibirRespuestaEscenario() {
    uint8_t respuesta;
    size_t s = 0;
    s += peer.recvall(&respuesta, sizeof(respuesta), &estaCerrado);
    if (s != sizeof(respuesta)) {
        throw std::runtime_error("Error en recibirRespuestaEscenario no recibio la respuesta \n");
    }
    return (int)respuesta;  // preguntar.
}


void Protocolo::enviarOperacionDireccion(const int& direccion) {
    uint8_t dirAEnviar = direccion;
    enviarOperacion(Operacion::DIRECCION);
    size_t s = 0;
    s += peer.sendall(&dirAEnviar, sizeof(dirAEnviar), &estaCerrado);
    if (s != sizeof(dirAEnviar)) {
        throw std::runtime_error("Error al enviar Operacion Direccion\n");
    }
}

void Protocolo::recibirDireccion(int& direccionGusano) {
    uint8_t dirGusanoRecv = 0;
    size_t s = 0;
    s += peer.recvall(&dirGusanoRecv, sizeof(dirGusanoRecv), &estaCerrado);
    if (s != sizeof(dirGusanoRecv)) {
        throw std::runtime_error("Error al recibir la direccion del gusano\n");
    }
    direccionGusano = (int)dirGusanoRecv;
}


void Protocolo::enviarOperacionMover() { enviarOperacion(Operacion::MOVER); }


void Protocolo::enviarOperacionSalto(const int& tipoSalto) {
    uint8_t tipoSaltoSend = tipoSalto;
    enviarOperacion(Operacion::JUMP);
    size_t s = 0;
    s += peer.sendall(&tipoSaltoSend, sizeof(tipoSaltoSend), &estaCerrado);
    if (s != sizeof(tipoSaltoSend)) {
        throw std::runtime_error("Error en el enviar Operacion Direccion\n");
    }
}

void Protocolo::recibirTipoSalto(int& tipoSalto) {
    uint8_t tipoSaltoRecv;
    size_t s = 0;
    s += peer.recvall(&tipoSaltoRecv, sizeof(tipoSaltoRecv), &estaCerrado);
    if (s != sizeof(tipoSaltoRecv)) {
        throw std::runtime_error("Error en el enviar Operacion Direccion\n");
    }
    tipoSalto = (int)tipoSaltoRecv;
}

void Protocolo::enviarOperacionDTO(const OperacionDTO& operacionDto) {
    Operacion tipoOper = operacionDto.getTipo();
    if (tipoOper == Operacion::SELECT) {
        enviarCreacionEscenario(operacionDto.getNombreEscenario());
    } else if (tipoOper == Operacion::DIRECCION) {
        enviarOperacionDireccion(operacionDto.getDireccion());
    } else if (tipoOper == Operacion::MOVER) {
        enviarOperacionMover();
    } else if (tipoOper == Operacion::JUMP) {
        enviarOperacionSalto(operacionDto.getSalto());
    }
}

OperacionDTO Protocolo::recibirOperacionDTO() {
    OperacionDTO operacionDTO;
    int unaOperacion = recibirOperacion();
    if (unaOperacion == Operacion::EXIT) {
        return operacionDTO;
    } else if (unaOperacion == Operacion::SELECT) {
        recvOperacionDTOSelect(operacionDTO);
    } else if (unaOperacion == Operacion::DIRECCION) {
        recvOperacionDTODir(operacionDTO);
    } else if (unaOperacion == Operacion::MOVER) {
        operacionDTO.setTipo(Operacion::MOVER);
    } else if (unaOperacion == Operacion::JUMP) {
        recvOperacionDTOJump(operacionDTO);
    }
    return operacionDTO;
}


void Protocolo::recvOperacionDTOSelect(OperacionDTO& operacionDTO) {
    operacionDTO.setTipo(Operacion::SELECT);
    std::string nombreEscenario;
    recibirCreacionEscenario(nombreEscenario);
    operacionDTO.setNombreEscenario(nombreEscenario);
}

void Protocolo::recvOperacionDTODir(OperacionDTO& operacionDTO) {
    operacionDTO.setTipo(Operacion::DIRECCION);
    int direccion;
    recibirDireccion(direccion);
    if (direccion == Direccion::DERECHA)
        operacionDTO.setDireccion(Direccion::DERECHA);
    else
        operacionDTO.setDireccion(Direccion::IZQUIERDA);
}

void Protocolo::recvOperacionDTOJump(OperacionDTO& operacionDTO) {
    operacionDTO.setTipo(Operacion::JUMP);
    int tipoSalto;
    recibirTipoSalto(tipoSalto);
    if (tipoSalto == TipoSalto::ADELANTE)
        operacionDTO.setSalto(TipoSalto::ADELANTE);
    else
        operacionDTO.setSalto(TipoSalto::ATRAS);
}

void Protocolo::enviarRespuestaDTO(const RespuestaDTO& rsptDTO) {
    if (rsptDTO.getRespuesta() == Respuesta::EXITO) {
        enviarRstpExitoCrearEscenario(rsptDTO.getPosFila(), rsptDTO.getPosCol());
    } else if (rsptDTO.getRespuesta() == Respuesta::ERROR) {
        enviarRsptErrorCrearEscenario();
    } else {
        enviarPosicionGusano(rsptDTO.getPosFila(), rsptDTO.getPosCol());
    }
}

RespuestaDTO Protocolo::recibirRsptDTO() {
    RespuestaDTO rsptDTO;
    recvPosicionesEnRspt(rsptDTO);
    return rsptDTO;
}

void Protocolo::recvPosicionesEnRspt(RespuestaDTO& rsptDTO) {
    unsigned int posFila, posCol;
    recibirPosicionesGusano(posFila, posCol);
    rsptDTO.setPosiciones(posFila, posCol);
}

RespuestaDTO Protocolo::recibirRsptEscenarioDTO() {
    RespuestaDTO rsptDTO;
    int rsptEscenario = recibirRespuestaEscenario();
    if (rsptEscenario == Respuesta::EXITO) {
        rsptDTO.setEstado(Respuesta::EXITO);
        recvPosicionesEnRspt(rsptDTO);
    } else {
        rsptDTO.setEstado(Respuesta::ERROR);
    }
    return rsptDTO;
}

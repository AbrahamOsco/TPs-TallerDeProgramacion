//
// Created by abraham on 19/09/23.
//

#include "common_respuestaDTO.h"
RespuestaDTO::RespuestaDTO(): estado(SIN_ESTADO), posFila(0), posCol(0) {}

void RespuestaDTO::setEstado(const Respuesta& unEstadoRspt) { this->estado = unEstadoRspt; }

void RespuestaDTO::setPosiciones(const unsigned int& unaPosFila, const unsigned int& unaPosCol) {
    this->posFila = unaPosFila;
    this->posCol = unaPosCol;
}

Respuesta RespuestaDTO::getRespuesta() const { return this->estado; }

unsigned int RespuestaDTO::getPosFila() const { return this->posFila; }

unsigned int RespuestaDTO::getPosCol() const { return this->posCol; }

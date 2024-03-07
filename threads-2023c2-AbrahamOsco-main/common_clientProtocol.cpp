//
// Created by abraham on 09/10/23.
//

#include "common_clientProtocol.h"

#include <iostream>


ClientProtocol::ClientProtocol(Socket& socket): Protocol(socket) {}

void ClientProtocol::sendAction(const ActionDTO& anAction) {
    if (anAction.getActionAct() == ACCION_CHAT) {
        sendANumberByte(NumOperation::CHAT);
        sendString(anAction.getMessage());
    }
}

AnswerDTO ClientProtocol::recvAnswer() {
    AnswerDTO unaRspt;
    int numOperacion = recvANumberByte();
    if (numOperacion == CIERRA_CONEXION) {
        throw std::runtime_error("Error Se cerro la conexion\n");
    } else if (numOperacion == NumOperation::ESTADO_PARTIDA) {
        unaRspt.setOperationNumber(NumOperation::ESTADO_PARTIDA);
        unaRspt.setNumberOfPlayers(recvANumberByte());
    } else if (numOperacion == NumOperation::MENSAJE_ENVIADO) {
        unaRspt.setOperationNumber(NumOperation::MENSAJE_ENVIADO);
        unaRspt.setChatMessage(recvString());
    }
    return unaRspt;
}

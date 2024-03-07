//
// Created by abraham on 09/10/23.
//

#include "common_serverProtocol.h"

ServerProtocol::ServerProtocol(Socket& socket): Protocol(socket) {}

ActionDTO ServerProtocol::recvAction() {
    ActionDTO unaAccion;
    int byteRecv = recvANumberByte();
    if (byteRecv == CIERRA_CONEXION)
        return unaAccion;
    if (byteRecv == NumOperation::CHAT)
        unaAccion.setActionAct(ACCION_CHAT);
    unaAccion.setMessage(recvString());
    return unaAccion;
}

void ServerProtocol::sendAnswer(const AnswerDTO& aAnswer) {
    NumOperation numOperacion = aAnswer.getOperationNumber();
    if (numOperacion == NumOperation::ESTADO_PARTIDA) {
        sendANumberByte(NumOperation::ESTADO_PARTIDA);
        sendANumberByte(aAnswer.getNumberOfPlayers());
    } else if (numOperacion == NumOperation::MENSAJE_ENVIADO) {
        sendANumberByte(NumOperation::MENSAJE_ENVIADO);
        sendString(aAnswer.getChatMessage());
    }
}

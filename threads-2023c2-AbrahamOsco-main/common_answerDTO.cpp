//
// Created by abraham on 27/09/23.
//

#include "common_answerDTO.h"

#include <iostream>

AnswerDTO::AnswerDTO(): numOperacion(SIN_ESTADO), cantPlayers(0) {}

AnswerDTO::AnswerDTO(const NumOperation& anOperation, const unsigned int& numberOfPlayers):
        numOperacion(anOperation), cantPlayers(numberOfPlayers), mensajeChat("") {}

AnswerDTO::AnswerDTO(const NumOperation& anOperation, const std::string& aChatMessage):
        numOperacion(anOperation), cantPlayers(0), mensajeChat(aChatMessage) {}


void AnswerDTO::setOperationNumber(const NumOperation& unNumeroOpe) {
    this->numOperacion = unNumeroOpe;
}

void AnswerDTO::setNumberOfPlayers(const unsigned int& numberOfPlayers) {
    this->cantPlayers = numberOfPlayers;
}

void AnswerDTO::setChatMessage(const std::string& aMessage) { this->mensajeChat = aMessage; }


NumOperation AnswerDTO::getOperationNumber() const { return numOperacion; }

unsigned int AnswerDTO::getNumberOfPlayers() const {
    if (numOperacion != NumOperation::ESTADO_PARTIDA) {
        throw std::runtime_error("Error no se puede pedir la cantidad de players con un "
                                 "NumOperacion distinto al de estado de partida\n");
    }
    return cantPlayers;
}

std::string AnswerDTO::getChatMessage() const {
    if (numOperacion != NumOperation::MENSAJE_ENVIADO) {
        throw std::runtime_error("Error no se puede pedir el mensaje con una NumOperacion distinto "
                                 "al de MENSAJE_EMVIADO\n");
    }
    return mensajeChat;
}

//
// Created by abraham on 27/09/23.
//

#include "client_client.h"

#include <utility>

#include "client_inputParser.h"
#include "common_actionDTO.h"
#include "common_answerDTO.h"
#include "common_clientProtocol.h"

Client::Client(const char* hostName, const char* serviceName):
        socket(Socket(hostName, serviceName)) {}

int Client::run() {
    ClientProtocol protocolo(socket);
    InputParser parser;
    while (parser.keepParsing()) {
        parser.parse();
        ActionDTO accionDto = parser.getAction();
        if (accionDto.getActionAct() == ACCION_READ) {
            readMessages(protocolo, accionDto.getNumberOfReads());
        } else if (accionDto.getActionAct() == ACCION_CHAT) {
            protocolo.sendAction(accionDto);
        }
    }
    return 0;
}

void Client::readMessages(ClientProtocol& protocol, const unsigned int& numberOfReads) {
    unsigned int i = 0;
    while (i < numberOfReads) {
        AnswerDTO unaRespuesta = protocol.recvAnswer();
        if (unaRespuesta.getOperationNumber() == NumOperation::ESTADO_PARTIDA) {
            std::cout << "Jugadores " << unaRespuesta.getNumberOfPlayers()
                      << ", esperando al resto de tus amigos...\n";
        } else if (unaRespuesta.getOperationNumber() == NumOperation::MENSAJE_ENVIADO) {
            std::cout << unaRespuesta.getChatMessage() << "\n";
        }
        i++;
    }
}

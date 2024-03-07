//
// Created by abraham on 27/09/23.
//

#include "server_server.h"

#include <iostream>
#include <utility>
#define EXIT_KEY 'q'
#include "common_serverProtocol.h"
#include "server_acceptorThread.h"

Server::Server(const char* serviceName): aceptador(Socket(serviceName)) {}

int Server::run() {
    AcceptorThread thrAceptador(aceptador);
    thrAceptador.start();
    while (std::cin.get() != EXIT_KEY) {}
    aceptador.totalClosure();
    thrAceptador.join();
    return 0;
}

void Server::runSingleThread() {
    Socket peer = aceptador.accept();
    ServerProtocol protocolo(peer);
    size_t contadorJug = 1;
    if (protocolo.isAvailable()) {
        sendStatusGame(protocolo, contadorJug);
    }
    while (protocolo.isAvailable()) {
        ActionDTO unaAccion = protocolo.recvAction();
        if (unaAccion.getActionAct() == ACCION_CHAT) {
            std::cout << unaAccion.getMessage() << std::endl;
            sendChatMessage(protocolo, unaAccion.getMessage());
        }
    }
    contadorJug--;
    printNumberOfPlayers(contadorJug);
}

void Server::sendStatusGame(ServerProtocol& protocol, const unsigned int& numberOfPlayers) {
    AnswerDTO rsptEstadoPartid;
    rsptEstadoPartid.setOperationNumber(NumOperation::ESTADO_PARTIDA);
    rsptEstadoPartid.setNumberOfPlayers(numberOfPlayers);
    protocol.sendAnswer(rsptEstadoPartid);
    printNumberOfPlayers(numberOfPlayers);
}

void Server::sendChatMessage(ServerProtocol& protocol, const std::string& message) {
    AnswerDTO rsptChat;
    rsptChat.setOperationNumber(NumOperation::MENSAJE_ENVIADO);
    rsptChat.setChatMessage(message);
    protocol.sendAnswer(rsptChat);
}

void Server::printNumberOfPlayers(const unsigned int& numberOfPlayers) {
    std::cout << "Jugadores " << numberOfPlayers << ", esperando al resto de tus amigos...\n";
}

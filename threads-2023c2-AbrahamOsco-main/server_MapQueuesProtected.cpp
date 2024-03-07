//
// Created by abraham on 28/09/23.
//

#include "server_MapQueuesProtected.h"

#include <string>


MapQueuesProtected::MapQueuesProtected(): cantJugAct(0) {}

void MapQueuesProtected::addNewQueue(const size_t& idThrClient, Queue<AnswerDTO>* aQueue) {
    std::unique_lock<std::mutex> lck(mtx);
    mapQueues[idThrClient] = aQueue;
    cantJugAct++;
    std::string unMensaje =
            "Jugadores " + std::to_string(cantJugAct) + ", esperando al resto de tus amigos...";
    std::cout << unMensaje << std::endl;
    AnswerDTO rsptEstadoPartid(NumOperation::ESTADO_PARTIDA, cantJugAct);
    for (auto& unElemento: mapQueues) {
        unElemento.second->push(rsptEstadoPartid);
    }
}

void MapQueuesProtected::pushAnswerDTO(const AnswerDTO& answerDto) {
    std::unique_lock<std::mutex> lck(mtx);
    for (auto& unElemento: mapQueues) {
        unElemento.second->push(answerDto);
    }
}

AnswerDTO MapQueuesProtected::popAnswerDTO(const size_t& idThrClient) {
    AnswerDTO unaRsptDTO = mapQueues[idThrClient]->pop();
    std::unique_lock<std::mutex> lck(mtx);
    return unaRsptDTO;
}

void MapQueuesProtected::notifyDisconnectedPlayers() {
    std::unique_lock<std::mutex> lck(mtx);
    cantJugAct--;
    std::string unMensaje =
            "Jugadores " + std::to_string(cantJugAct) + ", esperando al resto de tus amigos...";
    std::cout << unMensaje << std::endl;
    AnswerDTO rsptEstadoPartid(NumOperation::ESTADO_PARTIDA, cantJugAct);
    for (auto& unElemento: mapQueues) {
        unElemento.second->push(rsptEstadoPartid);
    }
}

void MapQueuesProtected::closeAndDeleteQueue(size_t idThread) {
    std::unique_lock<std::mutex> lck(mtx);
    mapQueues[idThread]->close();
    delete mapQueues[idThread];
    mapQueues.erase(idThread);
}

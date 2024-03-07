//
// Created by abraham on 28/09/23.
//

#include "server_receiverThread.h"

#include <string>

ReceiverThread::ReceiverThread(Socket& aSkt, std::atomic<bool>& aKeepTalking,
                               std::atomic<bool>& aIsAlive, MapQueuesProtected& mapQusProtec):
        sktPeer(aSkt),
        keepTalking(aKeepTalking),
        isAlive(aIsAlive),
        mapQueuesProtected(mapQusProtec) {}

void ReceiverThread::run() {
    ServerProtocol protocolo(sktPeer);
    while (keepTalking && protocolo.isAvailable()) {
        ActionDTO unaAccion = protocolo.recvAction();
        if (unaAccion.getActionAct() == ACCION_CHAT) {
            std::cout << unaAccion.getMessage() + "\n";
            AnswerDTO rsptChat(NumOperation::MENSAJE_ENVIADO, unaAccion.getMessage());
            mapQueuesProtected.pushAnswerDTO(rsptChat);
        }
    }
    isAlive = false;
    keepTalking = false;
    mapQueuesProtected.notifyDisconnectedPlayers();
}

//
// Created by abraham on 28/09/23.
//
#include "server_senderThread.h"

#include <string>

SenderThread::SenderThread(Socket& aSkt, std::atomic<bool>& aKeepTalking,
                           MapQueuesProtected& mapQsProtect, size_t unIdThread):
        sktPeer(aSkt),
        keepTalking(aKeepTalking),
        mapQueuesProtected(mapQsProtect),
        idThread(unIdThread) {}

void SenderThread::run() {
    ServerProtocol protocolo(sktPeer);
    while (keepTalking && protocolo.isAvailable()) {
        AnswerDTO unaRspt = mapQueuesProtected.popAnswerDTO(idThread);
        if (keepTalking) {
            protocolo.sendAnswer(unaRspt);
        } else {
            mapQueuesProtected.closeAndDeleteQueue(idThread);
        }
    }
}

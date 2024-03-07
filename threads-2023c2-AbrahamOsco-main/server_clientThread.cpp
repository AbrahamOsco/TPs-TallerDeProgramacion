//
// Created by abraham on 28/09/23.
//
#include "server_clientThread.h"

#include <utility>

#include "server_receiverThread.h"
#include "server_senderThread.h"

ClientThread::ClientThread(Socket sktPeer, MapQueuesProtected& aMapQueuProt, size_t unIdThr):
        peer(std::move(sktPeer)),
        keepTalking(true),
        isAlive(true),
        mapQueuesProtected(aMapQueuProt),
        idThread(unIdThr) {}

void ClientThread::run() {
    ReceiverThread thrRecv(peer, keepTalking, isAlive, mapQueuesProtected);
    thrRecv.start();
    SenderThread thrSend(peer, keepTalking, mapQueuesProtected, idThread);
    thrSend.start();
    thrSend.join();
    thrRecv.join();
}

bool ClientThread::isDead() const { return not isAlive; }

size_t ClientThread::getIdThread() const { return idThread; }


void ClientThread::kill() {
    keepTalking = false;
    peer.totalClosure();
}

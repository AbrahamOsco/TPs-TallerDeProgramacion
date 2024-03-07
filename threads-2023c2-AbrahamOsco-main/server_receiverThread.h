//
// Created by abraham on 28/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADRECEIVER_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADRECEIVER_H

#include <atomic>

#include "common_actionDTO.h"
#include "common_serverProtocol.h"
#include "common_socket.h"
#include "server_MapQueuesProtected.h"
#include "server_queue.h"
#include "server_thread.h"


class ReceiverThread: public Thread {
private:
    Socket& sktPeer;                         // cppcheck-suppress unusedStructMember
    std::atomic<bool>& keepTalking;          // cppcheck-suppress unusedStructMember
    std::atomic<bool>& isAlive;              // cppcheck-suppress unusedStructMember
    MapQueuesProtected& mapQueuesProtected;  // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    //  Recibe el sktPeer por referencia, al igual q los booleanos atomicos keepTalking e isAlive y
    //  el map de queueS protegida
    ReceiverThread(Socket& aSkt, std::atomic<bool>& aKeepTalking, std::atomic<bool>& aIsAlive,
                   MapQueuesProtected& mapQusProtec);

    //  Pre: -
    //  Post: Realiza los recv si son mensajes del tipo chat pushea el mensaje a todas las colas.
    virtual void run() override;

    //  Destructor
    virtual ~ReceiverThread() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADRECEIVER_H

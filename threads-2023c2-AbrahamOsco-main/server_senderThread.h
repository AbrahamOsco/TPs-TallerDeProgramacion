//
// Created by abraham on 28/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADSENDER_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADSENDER_H

#include <atomic>
#include <string>

#include "common_actionDTO.h"
#include "common_serverProtocol.h"
#include "common_socket.h"
#include "server_MapQueuesProtected.h"
#include "server_thread.h"

class SenderThread: public Thread {
private:
    Socket& sktPeer;                         // cppcheck-suppress unusedStructMember
    std::atomic<bool>& keepTalking;          // cppcheck-suppress unusedStructMember
    MapQueuesProtected& mapQueuesProtected;  // cppcheck-suppress unusedStructMember
    size_t idThread;                         // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    //  Recibe el sktPeer por referencia, el booleano atomico keepTalking, el map de queueS
    //  protegida y el idThread.
    SenderThread(Socket& aSkt, std::atomic<bool>& aKeepTalking, MapQueuesProtected& mapQsProtect,
                 size_t unIdThread);

    //  Pre: -.
    //  Post: Realiza los send de las "rsptDTO" que obtiene al popear de su cola respectiva (q la
    //  obtenemos por su idThread) si el cliente sigue conectado , si se desconecto el cliente no se
    //  envia nada.
    virtual void run() override;

    //  Destructor
    virtual ~SenderThread() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADSENDER_H

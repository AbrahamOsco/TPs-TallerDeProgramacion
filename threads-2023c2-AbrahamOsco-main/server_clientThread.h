//
// Created by abraham on 28/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADCLIENTE_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADCLIENTE_H

#include <atomic>

#include "common_protocol.h"
#include "common_socket.h"
#include "server_MapQueuesProtected.h"
#include "server_queue.h"
#include "server_thread.h"

class ClientThread: public Thread {
private:
    Socket peer;                             // cppcheck-suppress unusedStructMember
    std::atomic<bool> keepTalking;           // cppcheck-suppress unusedStructMember
    std::atomic<bool> isAlive;               // cppcheck-suppress unusedStructMember
    MapQueuesProtected& mapQueuesProtected;  // cppcheck-suppress unusedStructMember
    size_t idThread;                         // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    ClientThread(Socket sktPeer, MapQueuesProtected& aMapQueuProt, size_t unIdThr);

    //  Pre: -.
    //  Post: Retorna true si el thread cliente deja de estar conectado false en caso opuesto.
    bool isDead() const;

    //  Pre: -.
    //  Post: Retorna true si el thread cliente deja de estar conectado false en caso opuesto.
    void kill();

    //  Pre: -.
    //  Post: Retorna el id del thread.
    size_t getIdThread() const;

    //  Pre: -.
    //  Post: Lanza los threads Recv y los thread sender respectivamente, espera a que termina y los
    //  joinea.
    virtual void run() override;

    //  Destructor
    virtual ~ClientThread() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADCLIENTE_H

//
// Created by abraham on 22/07/23.
//

#ifndef THREADS_THREADCLIENTE_H
#define THREADS_THREADCLIENTE_H


#include <atomic>
#include "Socket.h"
#include "Thread.h"
#include "Protocolo.h"
#include "Juego.h"
#include "JuegoProtected.h"

class ThreadCliente : public Thread {
private:
    Socket peer;
    std::atomic<bool> keepTalking;
    std::atomic<bool> isRunning;
    JuegoProtected& juego;
    Protocolo protocolo;

public:
    ThreadCliente(Socket unSocketPeer, JuegoProtected& juego);


    virtual void run();

    void stop();

    bool clienteEstaCerrado();

    void operacionCrear();

    void operacionUnir();

    void operacionListar();
};


#endif //THREADS_THREADCLIENTE_H

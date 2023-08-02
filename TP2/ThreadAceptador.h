//
// Created by abraham on 22/07/23.
//

#ifndef THREADS_THREADACEPTADOR_H
#define THREADS_THREADACEPTADOR_H


#include <vector>
#include "Thread.h"
#include "Socket.h"
#include "ThreadCliente.h"
#include "JuegoProtected.h"


class ThreadAceptador : public Thread {
private:

    Socket sktAceptador;
    std::vector<ThreadCliente*> threadsClients;
    std::atomic<bool> isAccepting;
    JuegoProtected& unJuego;


public:
    ThreadAceptador(const char *serviceName, JuegoProtected& unJuego);

    virtual void run();


    void closeClientsFree();

    void closeAllClients();

    void closeSkt();

    void addNewCliente();
};


#endif //THREADS_THREADACEPTADOR_H

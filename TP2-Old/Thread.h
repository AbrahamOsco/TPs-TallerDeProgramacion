//
// Created by abraham on 22/07/23.
//

#ifndef THREADS_THREAD_H
#define THREADS_THREAD_H


#include <thread>

class Thread {
private:
    std::thread unHilo;

public:
    Thread();

    void start();

    void main();

    //Asi se hace un metodo abstracto en C++.
    virtual void run() = 0;

    //En las clases madres el destructor va siempre virtual.
    virtual  ~Thread();

    //Hacemos que no se pueda construir un thread usando uno o copiar directamente un thread (=).
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread& ) = delete;

    //Hacemos que el thread tampco se pueda mover por consturctor o se mueva con (=):
    Thread  (Thread&& otroThread) = delete;
    Thread& operator=(Thread&& otroThread) = delete;

    void join();
};


#endif //THREADS_THREAD_H

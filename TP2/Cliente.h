#ifndef THREADS_CLIENTE_H
#define THREADS_CLIENTE_H


#include "Socket.h"
#include "Protocolo.h"

class Cliente {
private:
    Socket socket;
public:
    Cliente(const char *hostName, const char *serviceName);

    int run();

    void operacionCrear(Protocolo &protocolo);

    void operacionUnirse(Protocolo &protocolo);

    void operacionListar(Protocolo &protocolo);

    void printRsptCrear(const std::string &unaRespuesta);

    void printRsptUnirse(const std::string &unaRespuesta);

};


#endif //THREADS_CLIENTE_H

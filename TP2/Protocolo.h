//
// Created by abraham on 14/07/23.
//

#ifndef THREADS_PROTOCOLO_H
#define THREADS_PROTOCOLO_H


#include <string>
#include "Socket.h"

class Protocolo {
private:
    bool wasClosed;

public:

    bool elSocketEstaCerrado();

    Protocolo();

    void enviarCadena(Socket &socket, const std::string &unaCadena);


    std::string recibirCadena(Socket &socket);
};


#endif //THREADS_PROTOCOLO_H

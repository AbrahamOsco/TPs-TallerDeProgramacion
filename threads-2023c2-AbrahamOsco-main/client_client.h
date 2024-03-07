//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_CLIENT_CLIENT_H
#define THREADS_2023C2_ABRAHAMOSCO_CLIENT_CLIENT_H

#include "common_clientProtocol.h"
#include "common_socket.h"

class Client {
private:
    Socket socket;  // cppcheck-suppress unusedStructMember

    //  Pre: Protocol inicializado
    //  Post: Lee *cantReads* mensajes del socket estos mensajes pueden ser del EstadoPartida o de
    //  un mensaje enviado.
    void readMessages(ClientProtocol& protocol, const unsigned int& numberOfReads);

public:
    // Constructor
    // Recibimos el hostName (IP) y el serviceName (Puerto).
    Client(const char* hostName, const char* serviceName);

    //  Pre: -
    //  Post: Realia el envio de mensajes al protocolo (chat), o lee desde el socket.
    int run();

    // Destructor
    ~Client() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_CLIENT_CLIENT_H

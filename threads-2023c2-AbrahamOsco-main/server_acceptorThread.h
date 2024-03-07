//
// Created by abraham on 28/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADACEPTADOR_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADACEPTADOR_H

#include <list>
#include <map>

#include "common_socket.h"
#include "server_MapQueuesProtected.h"
#include "server_clientThread.h"
#include "server_thread.h"

class AcceptorThread: public Thread {
private:
    Socket& aceptador;                      // cppcheck-suppress unusedStructMember
    std::list<ClientThread*> clientes;      // cppcheck-suppress unusedStructMember
    MapQueuesProtected mapQueuesProtected;  // cppcheck-suppress unusedStructMember

    //  Pre: -
    //  Post: Limpia los clientes que se desconectaron del servidor y libera  sus recursos
    //  respectivos.
    void cleanDeadClients();

    //  Pre: -
    //  Post: Killea todos los  cliente guardados, porque el servidor esta por cerrar .
    void killAllClients();

    //  Pre: recibe el idActual del cliente
    //  Post: Agrega un nuevo cliente y le asigna su respectivo idCliente.
    void addNewClient(size_t& idActual);

public:
    //  Constructor
    //  Recibe el socket por referencia
    explicit AcceptorThread(Socket& unSkt);

    //  Pre: -
    //  Post: Acepta nuevos clientes, limpia clientes muertos, y si cierra el skt aceptador killea
    //  los clientes. , .
    virtual void run() override;


    //  Destructor
    virtual ~AcceptorThread();
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_THREADACEPTADOR_H

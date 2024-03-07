//
// Created by abraham on 28/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_SERVER_MAPQUEUESPROTECTED_H
#define THREADS_2023C2_ABRAHAMOSCO_SERVER_MAPQUEUESPROTECTED_H

#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include "common_answerDTO.h"
#include "server_queue.h"

class MapQueuesProtected {
private:
    size_t cantJugAct;                              // cppcheck-suppress unusedStructMember
    std::map<size_t, Queue<AnswerDTO>*> mapQueues;  // cppcheck-suppress unusedStructMember
    std::mutex mtx;                                 // cppcheck-suppress unusedStructMember

public:
    //  Constructor del monitor
    MapQueuesProtected();

    //  Pre: Recibir la nueva cola cola y el idThread asociado a esa cola.
    //  Post: Agrega una nueva cola al diccionario de colas.
    void addNewQueue(const size_t& idThrClient, Queue<AnswerDTO>* aQueue);


    //  Pre: recibir una rsptDTO
    //  Post: pushea en todas las colas del diccionario la rsptDTO recibido como argumento.
    void pushAnswerDTO(const AnswerDTO& answerDto);

    //  Pre: recibir el idThread asociada a la cola donde queremos popear.
    //  Post: retorna la respuestaDTO popeado.
    AnswerDTO popAnswerDTO(const size_t& idThrClient);

    //  Pre: -.
    //  Post: Disminuye en 1 la cantidad de jugadores actuales, y pushea el estado de la partida a
    //  todas las colas.
    void notifyDisconnectedPlayers();

    //  Pre: La cola asociada a ese id existe en el map.
    //  Post: Cierra la cola, libera recursos de la queue en el map asociada a esa idTHread,
    //  luego se elimina esa queue evitando asi que pusheen mensajes los demas clientes
    //  a la queue de este cliente desconectado.
    void closeAndDeleteQueue(size_t idThread);

    ~MapQueuesProtected() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_SERVER_MAPQUEUESPROTECTED_H

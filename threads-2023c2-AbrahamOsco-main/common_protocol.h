//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOL_H
#define THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOL_H

#include <string>

#include "common_actionDTO.h"
#include "common_answerDTO.h"
#include "common_socket.h"
#define CIERRA_CONEXION -1
class Protocol {
private:
    Socket& socket;  // cppcheck-suppress unusedStructMember
    bool wasClosed;  // cppcheck-suppress unusedStructMember

protected:
    //  Pre: Socket inicializado
    //  Post: Envia la cadena (primero la longitud y luego la cadena en si).
    void sendString(const std::string& aString);

    //  Pre: Socket inicializado
    //  Post: Recibe la cadena (anteriormente enviada) y la retorna.
    std::string recvString();

    //  Pre: Socket incializado
    //  Post: Envia el numero recibido usando 1 byte.
    void sendANumberByte(const unsigned int& aNumber);

    //  Pre: Socket incializado
    //  Post: Recibe el byte (enviado anteriormente) y lo devuelve en caso de que el cliente se
    //  desconecte retorna -1.
    int recvANumberByte();

    //  Pre: Socket incializado
    //  Post: Envia el numero recibido usando 2 byte (lo pasa al endianness de la red).
    void sendNum2Bytes(const unsigned int& aNumber);

    //  Pre: Socket incializado
    //  Post: Recibe 2 bytes (enviado anteriormente) y lo devuelve (ya en el endiannes de la pc
    //  (ntohs) )c en caso de que el cliente se desconecte lanza excepcion.
    int recvNum2Bytes();

public:
    //  Constructor
    explicit Protocol(Socket& unSocket);

    //  Pre: Socket inicializado
    //  Post: Retorna true si el socket sigue "abierto", false en caso opuesto.
    bool isAvailable() const;

    //  Destructor
    ~Protocol() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_COMMON_PROTOCOL_H

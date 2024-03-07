//
// Created by abraham on 07/09/23.
//

#ifndef TP1_SOCKET_DB_SERVER_H


#define TP1_SOCKET_DB_SERVER_H


#include <string>
#include <utility>

#include "common_protocolo.h"
#include "common_socket.h"
#include "server_juego.h"


class Server {
private:
    Socket aceptador;  // cppcheck-suppress unusedStructMember
    Juego juego;       // cppcheck-suppress unusedStructMember


    //  Pre: Recibir el protocolo inicializado.
    //  Post: recibe el nombre escenario enviado por el cliente, y envia una respuesta a este
    //  mensaje.
    void seleccionarEscenario(Protocolo& protocolo, const std::string& nombreEscenario);

    //  Pre: Recibir el protocolo inicializado.
    //  Post: recibe la nueva direccion para el gusano enviada por el cliente y envia una respuesta
    //  a este mensaje.
    void girarAlGusano(Protocolo& protocolo, const Direccion& direccion);

    //  Pre: Recibir el protocolo inicializado.
    //  Post: mueve al gusano y envia una respuesta a este mensaje.
    void moverAlGusano(Protocolo& protocolo);

    //  Pre: Recibir el protocolo inicializado.
    //  Post: salta al gusano segun la direccionn  y envia una respuesta a este mensaje.
    void saltarGusano(Protocolo& protocolo, const TipoSalto& salto);

    //  Pre: Recibir el protocolo inicializado.
    //  Post: Envia  las posiciones del gusano y tambien las muestra por salida estandard.
    void enviarPosicionesDelGusano(Protocolo& protocolo);

    //  Pre: Recibir el protocolo inicializado.
    //  Post: Se encargara del manejo de las distintas operaciones.
    void realizarOperaciones(Protocolo& protocolo);

public:
    //  Constructor del server
    //  Pre: Recibe el serviceName (puerto) y el nombre del archivo
    //  Post: Devuelve un server en estado consistente.
    Server(const char* serviceName, const char* nombreArchivo);


    //  Pre: -
    //  Post: Inicia la ejecucion del servidor en espera de que se conecte un cliente y arranca la
    //  serie de mensajes
    int run();


    // Destructor del server.
    ~Server() = default;
};


#endif  // TP1_SOCKET_DB_SERVER_H

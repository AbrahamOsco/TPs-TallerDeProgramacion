//
//  Created by abraham on 08/09/23.
//

#ifndef TP1_SOCKET_DB_CLIENTE_H
#define TP1_SOCKET_DB_CLIENTE_H


#include <utility>

#include "common_protocolo.h"
#include "common_socket.h"

class Cliente {
private:
    Socket sktCliente;

    //  Pre: -
    // Post: Se delega la impresion de posiciones del gusano en este metodo.
    void imprimirPosicionesGusano(const RespuestaDTO& unaRsptDTO);

    //  Pre: -
    // Post: Se realiza el envio/recibo de una operacion delegando en el  protocolo por cada
    // operacion ingresado por el usuario.
    void realizarOperaciones(Protocolo& protocolo);


    //  Pre: -
    //  Post: Si la respuesta al crear el escenario fue negativa se lanzara excepcion, sino imprime
    //  las posiciones del gusano.
    void imprimirRsptEscenario(const RespuestaDTO& rsptDTO);


public:
    //  Constructor de la clase Cliente
    //  Pre: Recibe el hostName (puede ser cualquier IP) el serviceName tiene que coincidir con el
    //  del servidor. Post: inicaliza el socket del cliente que representa la conexion.
    Cliente(const char* hostName, const char* serviceName);

    //  Pre: Es el "main" del cliente donde se reciben distintas operaciones obtenidas desde un
    //  archivo, se necesitan input correctos Post: Se realiza la operacion indicada previamente
    //  delegandole al protocolo.
    int run();

    //  Destructor
    ~Cliente() = default;
};


#endif  // TP1_SOCKET_DB_CLIENTE_H

//
// Created by abraham on 07/09/23.
//

#ifndef TP1_SOCKET_DB_PROTOCOLO_H
#define TP1_SOCKET_DB_PROTOCOLO_H

#include <string>
#include <utility>

#include "common_operacionDTO.h"
#include "common_respuestaDTO.h"
#include "common_socket.h"


class Protocolo {
private:
    bool estaCerrado;  // cppcheck-suppress unusedStructMember
    Socket peer;       // cppcheck-suppress unusedStructMember
    //  Pre: Recibir el socket y el numero de la operacion a realizar.
    //  Post:Envia un byte que representa la operacion.
    void enviarOperacion(const int& operacion);

    //  Pre: El nombre del escenario a seleccionar.
    //  Post:Envia el numero de operacion, el largo del nombre del mapa y el nombre sin el '\0'.
    void enviarCreacionEscenario(const std::string& nombreEscenario);

    //  Pre: Recibir el nombre escenario.
    //  Post:Recibe el numero de operacion, largo y  nombre del escenario que sera asignado al
    //  string recibido como parametro.
    void recibirCreacionEscenario(std::string& nombreEscenario);

    //  Pre: -
    //  Post:Recibe la operacion (1byte) y retorna su equivalente en int.
    int recibirOperacion();

    //  Pre: -
    //  Post:Envia el byte que representa el error al intentar crear el escenario.
    void enviarRsptErrorCrearEscenario();

    //  Pre: Las posiciones (fila y columna) actual del gusano.
    //  Post:Envia el byte que representa el exito al crear el escenario y las posiciones del
    //  gusano.
    void enviarRstpExitoCrearEscenario(const unsigned int& posFila, const unsigned int& posColumna);
    //  Pre: -.
    //  Post:Recibe el byte de respuesta del escenario y retorna su equivalente en int.
    int recibirRespuestaEscenario();

    //  Pre: Los dos unsigned int para asignar la posiciones del gusano.
    //  Post:Recibe los bytes de las posiciones (fila y columna) y las asigna respectivamente a los
    //  parametros.
    void recibirPosicionesGusano(unsigned int& posFila, unsigned int& posCol);

    //  Pre: Recibir el tipo de direccion para girar el gusano 1(Derecha), 0
    //  (izquierda). Post:Envia el byte del tipo de operacion y el tipo de direccion recibdo por
    //  argumento.
    void enviarOperacionDireccion(const int& direccion);

    //  Pre: Recibir el tipo de direccion para girar el gusano 1(Derecha), 0
    //  (izquierda). Post:Envia el byte del tipo de operacion y el tipo de direccion recibdo por
    //  argumento.
    void enviarPosicionGusano(const unsigned int& posFila, const unsigned int& posColumna);
    //  Pre: -
    //  Post:Envia el byte que representa la operacion del tipo mover.
    void enviarOperacionMover();

    //  Pre: Recibir el tipo de salto para hacer 0->jump adelante, 1-> jump atras.
    //  Post:Envia el byte que representa la operacion del tipo salto y el tipo de salto recibido.
    void enviarOperacionSalto(const int& tipoSalto);

    //  Pre: Recibir  el tipo de direccion
    //  Post:Recibe el tipo de direccion y se lo asigna al uint8 recibido como argumento.
    void recibirDireccion(int& direccionGusano);

    //  Pre: Recibir el tipo de salto
    //  Post:Recibe el tipo de salto y se lo asigna al int recibido como argumento.
    void recibirTipoSalto(int& tipoSalto);

    //  Pre: recibir una rsptDTO
    //  Post: recibe las posciiones del gusano (fila y col) y las carga en la rsptDTO.
    void recvPosicionesEnRspt(RespuestaDTO& rsptDTO);

    //  Pre: recibir una operacionDTO
    //  Post: recibe el largo/nombre del escenario y lo carga en la operacionDTO.
    void recvOperacionDTOSelect(OperacionDTO& operacionDTO);

    //  Pre: recibir una operacionDTO
    //  Post: recibe la direccion y lo carga en la operacionDTO
    void recvOperacionDTODir(OperacionDTO& operacionDTO);

    //  Pre: recibir una operacionDTO
    //  Post: recibe el tipo de jump a hacer y lo carga en la operacionDTO
    void recvOperacionDTOJump(OperacionDTO& operacionDTO);

public:
    // Constructor de la clase Protocolo
    //  Pre: Se recibe el peer (y nos quedamos el ownership (por el std::move)) que representa la
    //  conexion con el cliente Post: Se inicializa el booleano que representa el cierre de la
    //  conexion en false.
    explicit Protocolo(Socket unSktPeer);

    //  Pre: -
    //  Post: Devuelve true si la conexion aun sigue disponbile, false en caso opuesto.
    bool estaDisponible() const;

    //  Pre:  Operacion DTO cargada con el input del usuario
    //  Post: Envia los bytes necesario segun los valores del tipo de operacion recibida.
    void enviarOperacionDTO(const OperacionDTO& operacionDto);

    //  Pre: -
    //  Post: Retorna una OperacionDTO cargada con el tipo de operacion ingresada por el usuario .
    OperacionDTO recibirOperacionDTO();

    //  Pre: -
    //  Post: Envia la respuesta de la operacion ingresada por el usuario.
    void enviarRespuestaDTO(const RespuestaDTO& rsptDTO);

    //  Pre: -
    //  Post: Retorna la respuesta de la operacion select ingresada por el usuario.
    RespuestaDTO recibirRsptEscenarioDTO();

    //  Pre: -
    //  Post: Retorna la respuesta a la operaicon ingresada por el usuario (dir, move, jump).
    RespuestaDTO recibirRsptDTO();

    // Destructor de protocolo;
    ~Protocolo() = default;
};


#endif  // TP1_SOCKET_DB_PROTOCOLO_H

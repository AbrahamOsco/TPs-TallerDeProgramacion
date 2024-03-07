//
// Created by abraham on 19/09/23.
//

#ifndef SOCKETS_2023C2_ABRAHAMOSCO_COMMON_RESPUESTADTO_H
#define SOCKETS_2023C2_ABRAHAMOSCO_COMMON_RESPUESTADTO_H

enum Respuesta { EXITO = 0, ERROR = 1, SIN_ESTADO = 2 };

class RespuestaDTO {
private:
    Respuesta estado;      // cppcheck-suppress unusedStructMember
    unsigned int posFila;  // cppcheck-suppress unusedStructMember
    unsigned int posCol;   // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    RespuestaDTO();

    //  Pre: -
    //  Post: se setea el estado de la respuesta.
    void setEstado(const Respuesta& unEstadoRspt);

    //  Pre:  Recibir las posicion de la fila y columna del gusano
    //  Post: se guardan las posiciones.
    void setPosiciones(const unsigned int& unaPosFila, const unsigned int& unaPosCol);

    //  Pre: -
    //  Post: se retorna el estado de la  respuesta.
    Respuesta getRespuesta() const;

    //  Pre: -
    //  Post: se retorna la fila del gusano.
    unsigned int getPosFila() const;

    //  Pre: -
    //  Post: se retorna la columna del gusano.
    unsigned int getPosCol() const;

    //  Destructor
    ~RespuestaDTO() = default;
};


#endif  // SOCKETS_2023C2_ABRAHAMOSCO_COMMON_RESPUESTADTO_H

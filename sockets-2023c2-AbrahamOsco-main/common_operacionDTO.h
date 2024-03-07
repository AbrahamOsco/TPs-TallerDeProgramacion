//
// Created by abraham on 18/09/23.
//

#ifndef SOCKETS_2023C2_ABRAHAMOSCO_COMMON_OPERACIONDTO_H
#define SOCKETS_2023C2_ABRAHAMOSCO_COMMON_OPERACIONDTO_H

#include <iostream>
#include <string>
enum Direccion { IZQUIERDA = 0, DERECHA = 1 };

enum TipoSalto { ADELANTE = 0, ATRAS = 1 };

enum Operacion { SELECT = 1, DIRECCION = 3, MOVER = 4, JUMP = 5, EXIT = -1 };


class OperacionDTO {
private:
    Operacion operacionNumerica;  // cppcheck-suppress unusedStructMember
    std::string nombreEscenario;  // cppcheck-suppress unusedStructMember
    Direccion direccion;          // cppcheck-suppress unusedStructMember
    TipoSalto salto;              // cppcheck-suppress unusedStructMember

public:
    //  Constructor OperacionDTO
    OperacionDTO();

    //  Pre: recibir el nombre del escenario
    //  Post: se guarda el nombre del escenario.
    void setNombreEscenario(const std::string& unNombreEscenario);

    //  Pre: recibir la direccion
    //  Post: se guarda la direccion.
    void setDireccion(const Direccion& unaDireccion);

    //  Pre: recibir el tipo de salto.
    //  Post: se guarda la direccion.
    void setSalto(const TipoSalto& unSalto);

    //  Pre: recibir el tipo de operacion.
    //  Post: se guarda el tipo de operacion.
    void setTipo(const Operacion& unaOperacion);

    //  Pre: -
    //  Post: se retorna el nombre del escenario.
    std::string getNombreEscenario() const;

    //  Pre: -
    //  Post: se retorna la direccion
    Direccion getDireccion() const;

    //  Pre: -
    //  Post: se retorna el tipo de salto.
    TipoSalto getSalto() const;

    //  Pre: -
    //  Post: se retorna el tipo de operacion.
    Operacion getTipo() const;

    //  destructor
    ~OperacionDTO() = default;
};


#endif  // SOCKETS_2023C2_ABRAHAMOSCO_COMMON_OPERACIONDTO_H

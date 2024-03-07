//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_COMMON_ACTIONDTO_H
#define THREADS_2023C2_ABRAHAMOSCO_COMMON_ACTIONDTO_H
#include <string>
#define ACCION_CHAT "Chat"
#define ACCION_READ "Read"
#define ACCION_EXIT "Exit"

class ActionDTO {
private:
    std::string accionAct;   // cppcheck-suppress unusedStructMember
    std::string mensaje;     // cppcheck-suppress unusedStructMember
    unsigned int cantReads;  // cppcheck-suppress unusedStructMember

public:
    //  Constructor
    ActionDTO();

    //  Pre: -
    //  Post: Setea el tipo de accion con el string recibido.
    void setActionAct(const std::string& anAction);

    //  Pre: -
    //  Post: Setea el mensaje con el string recibido.
    void setMessage(const std::string& aMessage);

    //  Pre: -
    //  Post: Setea la cantidad de Reads.
    void setNumberOfReads(const unsigned int& numberOfReads);

    //  Pre: -
    //  Post: Retorna el tipo de accion actual.
    std::string getActionAct() const;

    //  Pre: -
    //  Post: Retorna el mensaje.
    std::string getMessage() const;

    //  Pre: -
    //  Post: Retorna la cantidad de reads.
    unsigned int getNumberOfReads() const;

    //  Destructor
    ~ActionDTO() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_COMMON_ACTIONDTO_H

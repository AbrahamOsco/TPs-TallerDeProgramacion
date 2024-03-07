//
// Created by abraham on 27/09/23.
//

#ifndef THREADS_2023C2_ABRAHAMOSCO_COMMON_ANSWERDTO_H
#define THREADS_2023C2_ABRAHAMOSCO_COMMON_ANSWERDTO_H

enum NumOperation { SIN_ESTADO = -1, CHAT = 5, ESTADO_PARTIDA = 6, MENSAJE_ENVIADO = 9 };
#include <string>

class AnswerDTO {
private:
    NumOperation numOperacion;  // cppcheck-suppress unusedStructMember
    unsigned int cantPlayers;   // cppcheck-suppress unusedStructMember
    std::string mensajeChat;    // cppcheck-suppress unusedStructMember

public:
    //  Consturctor de AnswerDTO
    AnswerDTO();

    //  Constructor de AnswerDTO creado para el tipo de operacion ESTADO_PARTIDA
    AnswerDTO(const NumOperation& anOperation, const unsigned int& numberOfPlayers);

    //  Constructor de AnswerDTO creado para el tipo de operacion MENSAJE_ENVIADO
    AnswerDTO(const NumOperation& anOperation, const std::string& aChatMessage);
    //  Pre: -
    //  Post: Setea el numeroDeOperacion.
    void setOperationNumber(const NumOperation& unNumeroOpe);

    //  Pre: -
    //  Post: Setea la cantidad de jugadores.
    void setNumberOfPlayers(const unsigned int& numberOfPlayers);

    //  Pre: -
    //  Post: Setea el mensaje
    void setChatMessage(const std::string& aMessage);

    //  Pre: -
    //  Post: Retorna el enum numero de operacion Actual.
    NumOperation getOperationNumber() const;

    //  Pre: -
    //  Post: Retorna la cantidad de jugadores.
    unsigned int getNumberOfPlayers() const;

    //  Pre: -
    //  Post: Retorna el mensaje de chat.
    std::string getChatMessage() const;

    //  Destructor de AnswerDTO
    ~AnswerDTO() = default;
};


#endif  // THREADS_2023C2_ABRAHAMOSCO_COMMON_ANSWERDTO_H

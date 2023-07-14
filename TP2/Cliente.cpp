#include <string>
#include <iostream>
#include "Cliente.h"
#include "Protocolo.h"

Cliente::Cliente(const char *hostName, const char *serviceName) : socket(hostName, serviceName){

}

int Cliente::run() {
    std::string inputUsuario;
    Protocolo unProtocolo;
    while(inputUsuario != "fin"){
        std::cout << "Ingrese un comando crear, listar, unirse o fin \n";
        std::cin >> inputUsuario;
        if(inputUsuario == "crear"){
            operacionCrear(unProtocolo);
        } else if (inputUsuario == "unirse"){
            operacionUnirse(unProtocolo);
        } else if (inputUsuario == "listar"){
            operacionListar(unProtocolo);
        }
    }
    return 0;

}

void Cliente::operacionCrear(Protocolo &protocolo) {
    std::string cantJugadores, nombrePartida;
    std::cin >> cantJugadores;
    getline(std::cin, nombrePartida,'\n');
    nombrePartida = nombrePartida.substr(1); //parseo un string desde la posicion 1 hasta el final.

    protocolo.enviarCadena(socket, "CREAR");
    protocolo.enviarCadena(socket, " ");
    protocolo.enviarCadena(socket, cantJugadores);
    protocolo.enviarCadena(socket, " ");
    protocolo.enviarCadena(socket, nombrePartida);
    protocolo.enviarCadena(socket, "\n\n");

    printRsptCrear(protocolo.recibirCadena(socket));
}

void Cliente::operacionUnirse(Protocolo &protocolo) {
    std::string nombrePartida;
    // al recibir "unirse partida 123" -> con cin obtenemos unirse y con getline obtenemos " partida 123" con espacio
    getline(std::cin, nombrePartida, '\n');
    nombrePartida = nombrePartida.substr(1);
    protocolo.enviarCadena(socket, "UNIR");
    protocolo.enviarCadena(socket, nombrePartida);
    protocolo.enviarCadena(socket, "\n\n");

    printRsptUnirse(protocolo.recibirCadena(socket));
}

void Cliente::operacionListar(Protocolo &protocolo) {
    protocolo.enviarCadena(socket, "LISTAR");
    protocolo.enviarCadena(socket, "\n\n");
    std:: cout << protocolo.recibirCadena(socket);
}

void Cliente::printRsptCrear(const std::string &unaRespuesta) {
    if(unaRespuesta == "OK\n\n"){
        std::cout << "Creación exitosa\n";
    } else if (unaRespuesta == "ERROR\n\n"){
        std::cout << "Creación fallida\n";
    }

}

void Cliente::printRsptUnirse(const std::string &unaRespuesta) {
    if(unaRespuesta == "OK\n\n"){
        std::cout << "Unión exitosa\n";
    } else if (unaRespuesta == "ERROR\n\n"){
        std::cout << "Unión fallida\n";
    }
}


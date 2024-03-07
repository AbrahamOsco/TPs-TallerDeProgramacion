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
    protocolo.enviarPeticionCrearPartida(socket, nombrePartida, cantJugadores);
    std::string  rsptCrear = protocolo.recibirResultado(socket);
    printRsptCrear( rsptCrear);
}

void Cliente::operacionUnirse(Protocolo &protocolo) {
    std::string nombrePartida;
    getline(std::cin, nombrePartida, '\n');
    nombrePartida = nombrePartida.substr(1);  // obtenemos " duelo"  lo pasamos a "duelo".
    protocolo.enviarPeticionUnirsePartida(socket, nombrePartida);
    std::string respuestaUnirse = protocolo.recibirResultado(socket);
    printRsptUnirse(respuestaUnirse);
}

void Cliente::operacionListar(Protocolo &protocolo) {
    protocolo.enviarCadena(socket, "LISTAR");
    protocolo.enviarCadena(socket, "\n\n");
    std::string rsptListar = protocolo.recibirCadena(socket);
    std:: cout << rsptListar;
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


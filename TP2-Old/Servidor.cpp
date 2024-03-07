#include <string>
#include <iostream>
#include "Servidor.h"
#include "Protocolo.h"
#include "ThreadAceptador.h"
#include "liberror.h"

Servidor::Servidor(const char *serviceName) :
                                              threadAceptador(serviceName, unJuego )    {
}

int Servidor::run() {
    try{
        std::string input = "";
        threadAceptador.start(); //lanzamos el hilo aceptador
        std::cout<< "Ingrese q para cerrar el servidor: \n";
        while(input != "q"){
            getline(std::cin, input, '\n');
        }
        threadAceptador.closeSkt();
        threadAceptador.join();
    }catch( ... ){
        std::cerr << "Se atrapo una excepcion desconocida \n";
        return 1;
    }
    return 0;
}
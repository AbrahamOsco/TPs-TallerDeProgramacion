#include <netdb.h>
#include <string>
#include <cstring>
#include <iostream>
#include "Resolver.h"


Resolver::Resolver(const char *hostName, const char *serviceName, bool tipoPasivo) {
    struct addrinfo hints;
    //inicializamos todo de  hints en cero.
    memset(&hints, 0, sizeof(struct addrinfo ) );
    hints.ai_family = AF_INET; //Usarmeos la familia de direcciones IPv4. para IPv6 AF_INET6.
    hints.ai_socktype =   //Usaremos un sktAceptador TCP.
    hints.ai_flags = tipoPasivo ? AI_PASSIVE : 0 ; //Si el nodo es null y el ai_flags es AI_PASSIVE las direcciones de sockets seran adecuadas para el bind.

    // Ahora usamos getaddrinfo para obtener las direcciones seguun el hostanme y service que busco:
    int s = getaddrinfo(hostName, serviceName, &hints, &this->results  );

    if( s!=0){
        if ( s == EAI_SYSTEM){
            std::string mensaje = "Se lanza excepcion error : EAI_SYSTEM" + std::to_string(errno);
            std::cerr << mensaje;
            throw mensaje;
        } else {
            std::cerr << "Otro erro distintos a EAI_SYSTEM";
            throw "Otro erro distintos a EAI_SYSTEM";
        }
    }
    this->next = this->results;
}

bool Resolver::hasNext(){
    return (this->next != nullptr);
}

struct addrinfo* Resolver::getNext(){
    struct addrinfo* next = this->next;
    this->next = next->ai_next;
    return next;
}

Resolver::~Resolver(){
    if(this->results){
        ::freeaddrinfo(this->results);
    }
}

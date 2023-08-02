#include <stdexcept>
#include <netinet/in.h>
#include <cstring>
#include "Protocolo.h"


Protocolo::Protocolo() : wasClosed(false) {
}

bool Protocolo::elSocketEstaCerrado(){
    return wasClosed;
}

void Protocolo::enviarCadena(Socket& socket, const std::string &unaCadena){
    int s = 0;       //primero enviamos su largo y luego el texto.
    uint32_t largoCadena = unaCadena.size();
    largoCadena = htonl(largoCadena);
    s += socket.sendAll(&largoCadena, sizeof(largoCadena), &wasClosed);
    s += socket.sendAll(unaCadena.data(), unaCadena.size(), &wasClosed);

    if ( s != sizeof(largoCadena) + unaCadena.size()  ){
        throw std::runtime_error("Error en el envio de la cadena\n");
    }
}

std::string Protocolo::recibirCadena(Socket& socket){
    int s = 0;
    uint32_t  largoCadena = 0;
    s += socket.recvAll(&largoCadena, sizeof(largoCadena), &wasClosed );
    if (wasClosed) return ""; // agrege yo caso de que no leyo y esta cerrado el skt devolvemos sz.
    largoCadena = ntohl(largoCadena);
    char buffRecvCadena[largoCadena], buffRetonar[largoCadena+1];

    s += socket.recvAll(&buffRecvCadena, sizeof(buffRecvCadena), &wasClosed);

    if( s != sizeof(largoCadena) + sizeof(buffRecvCadena) ){
        throw std::runtime_error("Error en el recibo de la cadena\n");
    }
    strncpy(buffRetonar, buffRecvCadena, largoCadena);
    buffRetonar[largoCadena] = '\0';

    return buffRetonar;
}


void Protocolo::recibirPeticionCrearPartida(Socket &socket, std::string& unNombrePartida, std::string& cantJugReq) {
    std::string cadenaVacia, saltos;
    cadenaVacia = recibirCadena(socket);
    cantJugReq = recibirCadena(socket);
    cadenaVacia = recibirCadena(socket);
    unNombrePartida = recibirCadena(socket);
    saltos = recibirCadena(socket);
}

void Protocolo::enviarPeticionCrearPartida(Socket &socket, const std::string &nombrePartida, const std::string &cantJugReq) {
    enviarCadena(socket, "CREAR");
    enviarCadena(socket, " ");
    enviarCadena(socket, cantJugReq);
    enviarCadena(socket, " ");
    enviarCadena(socket, nombrePartida);
    enviarCadena(socket, "\n\n");
}

void Protocolo::enviarPeticionUnirsePartida(Socket &socket, const std::string &unNombrePartida) {
    enviarCadena(socket, "UNIR");
    enviarCadena(socket, unNombrePartida);
    enviarCadena(socket, "\n\n");
}

void Protocolo::recibirPeticionUnirsePartida(Socket &socket, std::string &unNombrePartida) {
    unNombrePartida = recibirCadena(socket);
    std::string saltos = recibirCadena(socket);
}

void Protocolo::enviarResultado(Socket &socket, const bool &resultadoPeticion) {
    if (resultadoPeticion) enviarCadena(socket, "OK\n\n");
    else enviarCadena(socket, "ERROR\n\n");
}
std::string Protocolo::recibirResultado(Socket& socket){
    return recibirCadena(socket);
}



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

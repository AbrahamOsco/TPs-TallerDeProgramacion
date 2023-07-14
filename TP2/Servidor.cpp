#include <string>
#include <iostream>
#include "Servidor.h"
#include "Protocolo.h"

Servidor::Servidor(const char *serviceName) : socket(serviceName)  {
}

int Servidor::run() {
    try{
        std::string unComando = "";
        Protocolo protocolo;
        Socket peer = socket.accept();
        while(not protocolo.elSocketEstaCerrado()){
            unComando = recibirComando(peer, protocolo);
            if( unComando == "CREAR"){
                operacionCrear(peer, protocolo);
            } else if (unComando == "UNIR"){
                operacionUnir(peer, protocolo);
            } else if (unComando == "LISTAR"){
                operacionListar(peer, protocolo);
            }
        }
    }catch( ... ){
        return 1;
    }

    return 0;
}

std::string Servidor::recibirComando(Socket &socket, Protocolo &protocolo){
    return protocolo.recibirCadena(socket);
}

void Servidor::operacionCrear(Socket &socket, Protocolo &protocolo) {
    std::string cadenaVacia, cantJugReq, nombrePartida, saltos;
    cadenaVacia = protocolo.recibirCadena(socket);
    cantJugReq = protocolo.recibirCadena(socket);
    cadenaVacia = protocolo.recibirCadena(socket);
    nombrePartida = protocolo.recibirCadena(socket);
    saltos = protocolo.recibirCadena(socket);
    if( juego.crearPartida(nombrePartida, std::stoi(cantJugReq) ) )
        protocolo.enviarCadena(socket, "OK\n\n");
    else protocolo.enviarCadena(socket, "ERROR\n\n");


}

void Servidor::operacionUnir(Socket &socket, Protocolo &protocolo) {
    std::string nombrePartida;
    nombrePartida = protocolo.recibirCadena(socket);
    if( juego.unirsePartida(nombrePartida) )
        protocolo.enviarCadena(socket, "OK\n\n");
    else protocolo.enviarCadena(socket, "ERROR\n\n");


}

void Servidor::operacionListar(Socket &socket, Protocolo &protocolo) {
    std:: string saltos;
    saltos = protocolo.recibirCadena(socket);
    std::string respuesta = "OK\n" + juego.listarPartidas() + "\n";
    protocolo.enviarCadena(socket, respuesta);

}

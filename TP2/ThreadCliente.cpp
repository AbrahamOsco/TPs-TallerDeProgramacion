//
// Created by abraham on 22/07/23.
//

#include <iostream>
#include "ThreadCliente.h"
#include "Protocolo.h"
#include "Juego.h"

ThreadCliente::ThreadCliente(Socket unSocketPeer, JuegoProtected& juego) : peer(std::move(unSocketPeer)),
                                    isRunning(true), keepTalking(true), juego(juego){
}

void ThreadCliente::run(){
    while(keepTalking && not protocolo.elSocketEstaCerrado()){
        std::string unComando = protocolo.recibirCadena(peer);
        if( unComando == "CREAR"){
            operacionCrear();
        } else if (unComando == "UNIR"){
            operacionUnir();
        } else if (unComando == "LISTAR"){
            operacionListar();
        }
    }
    isRunning = false;
}

//violento per efectivo.
void ThreadCliente::stop(){
    keepTalking = false;
    peer.closeSkt();
}

bool ThreadCliente::clienteEstaCerrado(){
    return not isRunning;
}

void ThreadCliente::operacionCrear() {
    std::string cantJugReq, nombrePartida;
    this->protocolo.recibirPeticionCrearPartida(peer, nombrePartida, cantJugReq);
    bool resultado = juego.crearPartida(nombrePartida, std::stoi(cantJugReq) );
    this->protocolo.enviarResultado(peer, resultado );
}

void ThreadCliente::operacionUnir() {
    std::string nombrePartida;
    protocolo.recibirPeticionUnirsePartida(peer, nombrePartida);
    bool resultado = juego.unirsePartida(nombrePartida);
    this->protocolo.enviarResultado(peer, resultado );
}

void ThreadCliente::operacionListar() {
    std:: string saltos = protocolo.recibirCadena(peer);
    std::string respuesta = "OK\n" + juego.listarPartidas();
    this->protocolo.enviarCadena(peer, respuesta);
}


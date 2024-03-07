//
// Created by abraham on 22/07/23.
//

#include <iostream>
#include "ThreadAceptador.h"
#include "Socket.h"
#include "liberror.h"


ThreadAceptador::ThreadAceptador(const char *serviceName, JuegoProtected& unJuego) : sktAceptador(serviceName),
                                                                         isAccepting(true), unJuego(unJuego) {
}

void ThreadAceptador::addNewCliente(){
    Socket unPeer = this->sktAceptador.accept();
    ThreadCliente* unCliente = new ThreadCliente(std::move(unPeer), unJuego);
    unCliente->start();
    std::cout <<"Se conecto un nuevo cliente \n";
    threadsClients.push_back(unCliente);
}

void ThreadAceptador::run(){
    try{
        while(isAccepting){
            addNewCliente();
            closeClientsFree();
        }
    }catch( const LibError& sktAceptError){
        std::cerr <<"En el thread aceptador: " <<  sktAceptError.what();
        closeAllClients();
        return;
    }catch( ... ){
        std::cerr << "Se atrapo una excepcion desconocidaEn el ThreadAceptador\n";
        closeAllClients();
        return;
    }
}

void ThreadAceptador::closeClientsFree(){
    int tamTotalIni = threadsClients.size();
    for(int i = 0; i < tamTotalIni; i++ ){
        if( i < threadsClients.size() and threadsClients[i]->clienteEstaCerrado() ){
            threadsClients[i]->join(); //joineamos
            delete threadsClients[i]; //liberamos memoria
            threadsClients.erase(threadsClients.begin() + i); //lo sacamos de la lista.
            i-=1;
        }
    }
}

void ThreadAceptador::closeAllClients(){
    int tamanioTotIni = threadsClients.size();
    for(int i = 0 ; i < tamanioTotIni; i++){
        threadsClients[0]->stop();
        threadsClients[0]->join();
        delete threadsClients[0];
        threadsClients.erase(threadsClients.begin());
        std::cout<<"Se detiene un cliente\n";
    }
}

void ThreadAceptador::closeSkt() {
    isAccepting = false;
    sktAceptador.closeSkt();
}


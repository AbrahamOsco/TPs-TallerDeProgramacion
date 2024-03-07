//
// Created by abraham on 28/09/23.
//
#include "server_acceptorThread.h"

#include <string>
#include <utility>

#include "common_answerDTO.h"
#include "server_queue.h"

AcceptorThread::AcceptorThread(Socket& unSocket): aceptador(unSocket) {}


void AcceptorThread::run() {
    try {
        size_t idActual = 0;
        while (true) {
            addNewClient(idActual);
            cleanDeadClients();
        }
    } catch (const std::exception& e) {
        killAllClients();
    } catch (...) {
        std::cerr << "Unknown error\n";
    }
}

void AcceptorThread::addNewClient(size_t& idActual) {
    size_t nuevoId = idActual;
    Socket sktPeer = aceptador.accept();
    Queue<AnswerDTO>* unaCola = new Queue<AnswerDTO>;
    mapQueuesProtected.addNewQueue(nuevoId, unaCola);
    ClientThread* thrCliente = new ClientThread(std::move(sktPeer), mapQueuesProtected, nuevoId);
    thrCliente->start();
    clientes.push_back(thrCliente);
    idActual++;
}

void AcceptorThread::cleanDeadClients() {
    clientes.remove_if([this](ClientThread* unCliente) {
        if (unCliente->isDead()) {
            unCliente->join();
            delete unCliente;
            return true;
        }
        return false;
    });
}

void AcceptorThread::killAllClients() {
    for (auto& unCliente: clientes) {
        unCliente->kill();
        unCliente->join();
        delete unCliente;
    }
    clientes.clear();
}

AcceptorThread::~AcceptorThread() {}

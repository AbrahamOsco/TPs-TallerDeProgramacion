//
// Created by abraham on 22/07/23.
//

#include <iostream>
#include "Thread.h"

Thread::Thread() {}

void Thread::start(){
    //Aca lanzamos el hilo la funcion concurrente es main.
    this->unHilo = std::thread{ &Thread::main, this  };
}

void Thread::main(){
    try{
        this->run();
    }catch (const std::exception& e ){
        std::cerr << "unexpected exception in main-Thread e.what():" <<  e.what() << "\n";
    }catch (...){
        std::cerr << "Unknown exception in main-Thread \n";
    }
}

void Thread::join(){
    unHilo.join();
}

Thread::~Thread() {
}






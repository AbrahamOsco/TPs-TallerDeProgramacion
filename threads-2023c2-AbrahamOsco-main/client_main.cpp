//
// Created by abraham on 27/09/23.
//
#include <iostream>

#include "client_client.h"

int main(int argc, const char* argv[]) {
    try {
        if (argc <= 2)
            return 1;
        Client cliente(argv[1], argv[2]);
        return cliente.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido \n";
    }
}

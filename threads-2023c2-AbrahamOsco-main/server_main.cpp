//
// Created by abraham on 27/09/23.
//
#include <iostream>

#include "server_server.h"

int main(int argc, const char* argv[]) {
    try {
        if (argc < 1)
            return 1;
        Server server(argv[1]);
        return server.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return 1;
    }
}

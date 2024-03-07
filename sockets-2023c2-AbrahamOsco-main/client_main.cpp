#include <iostream>

#include "client_cliente.h"


int main(int argc, const char* argv[]) {
    try {
        if (argc <= 2)
            return 1;
        Cliente cliente(argv[1], argv[2]);
        return cliente.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Error desconocido\n";
        return 1;
    }
}

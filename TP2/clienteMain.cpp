

#include "Cliente.h"

int main(int argc, const char* argv[]) {
    Cliente cliente(argv[1], argv[2]);
    return cliente.run();
}

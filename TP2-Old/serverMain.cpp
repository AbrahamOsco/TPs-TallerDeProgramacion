#include <iostream>
#include "Servidor.h"


int main(int argc, const char* argv[]) {
    Servidor servidor(argv[1]);
    return servidor.run();
}

//
// Created by abraham on 28/09/23.
//

#include "server_thread.h"

void Thread::start() { thread = std::thread(&Thread::main, this); }

void Thread::main() {
    try {
        run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown error\n";
    }
}

void Thread::join() { thread.join(); }

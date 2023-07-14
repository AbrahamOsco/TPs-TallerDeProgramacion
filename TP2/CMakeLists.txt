cmake_minimum_required(VERSION 3.25)
project(Threads)

set(CMAKE_CXX_STANDARD 17)

add_executable(Threads serverMain.cpp Servidor.cpp Servidor.h Partida.cpp Partida.h Socket.cpp Socket.h Resolver.cpp Resolver.h Juego.cpp Juego.h Cliente.cpp Cliente.h  Protocolo.cpp Protocolo.h)

//
// Created by abraham on 06/09/23.
//

#include "server_archivoEscenario.h"

#include <iostream>
#include <sstream>
#include <string>

ArchivoEscenario::ArchivoEscenario(const std::string& nombreArchivo) {
    this->cantFilas = 0;
    this->cantColumnas = 0;
    this->nombreMapa = "";
    unArchivo.open("escenarios.txt");
    if (unArchivo.fail()) {
        throw std::runtime_error("ERROR al abrir el archivo");
    }
}

bool ArchivoEscenario::cargarEscenario(const std::string& nombreEscenario) {
    std::string unaFilaDelMapa, buscarEscenario;
    bool encontro = false;
    while (!encontro && getline(unArchivo, buscarEscenario, '\n')) {
        if (buscarEscenario.find(nombreEscenario) != std::string::npos) {
            encontro = true;
        }
    }
    if (!encontro)
        return encontro;
    std::istringstream datosDelMapa(buscarEscenario);
    datosDelMapa >> this->cantColumnas >> this->cantFilas >> this->nombreMapa;
    int contador = 0;
    while (getline(unArchivo, unaFilaDelMapa, '\n') && contador < cantFilas) {
        this->filasMapa.push_back(unaFilaDelMapa);
        contador++;
    }
    return encontro;
}

void ArchivoEscenario::getFilaColYNombreMapa(int& fila, int& columna,
                                             std::string& nombreMapa) const {
    fila = this->cantFilas;
    columna = this->cantColumnas;
    nombreMapa = this->nombreMapa;
}

std::vector<std::string> ArchivoEscenario::getTableroInicial() const { return filasMapa; }

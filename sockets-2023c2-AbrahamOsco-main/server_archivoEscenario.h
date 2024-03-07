//
// Created by abraham on 06/09/23.
//

#ifndef TP1_SOCKET_DB_ARCHIVOESCENARIO_H
#define TP1_SOCKET_DB_ARCHIVOESCENARIO_H

#include <fstream>
#include <string>
#include <vector>

class ArchivoEscenario {
private:
    std::ifstream unArchivo;             // cppcheck-suppress unusedStructMember
    int cantFilas;                       // cppcheck-suppress unusedStructMember
    int cantColumnas;                    // cppcheck-suppress unusedStructMember
    std::string nombreMapa;              // cppcheck-suppress unusedStructMember
    std::vector<std::string> filasMapa;  // cppcheck-suppress unusedStructMember

public:
    //  Constructor de la clase ArchivoEscenario
    //  Pre: Recibe el nombre del archivo donde se encontraran los diversos escenarios.
    //  Post: Abre el archivo cuyo nombre es pasado por parametro.
    explicit ArchivoEscenario(const std::string& nombreArchivo);

    //  Pre: Recibe el nombre del escenario a usar (tablero + filas + columnas + nombre).
    //  Post:Lee el escenario (tablero) del nombre elegido ademas de la cantidad de filas, columnas,
    //  nombre, retorna true si existe el nombre del escenario, false en caso opuesto.
    bool cargarEscenario(const std::string& nombreEscenario);

    //  Pre: Haber cargado el escenario antes.
    //  Post: Carga el valor de la fila, columna y el nombre del mapa con su respectivo argumento
    //  asociado.
    void getFilaColYNombreMapa(int& fila, int& columna, std::string& nombreMapa) const;

    //  Pre: Haber cargado el escenario antes.
    //  Post: Obtiene el tablero asociado al nombre del escenario pasado anteriormente.
    std::vector<std::string> getTableroInicial() const;

    //  Destructor.
    ~ArchivoEscenario() = default;
};


#endif  // TP1_SOCKET_DB_ARCHIVOESCENARIO_H

#include <iostream>
#include <string>
#include <unistd.h>
#include "funciones.h"
using namespace std;

// Prototipos de funciones
void genTableros(int numTableros) {
    std::cout << "Generando " << numTableros << " tableros..." << std::endl;
    // Lógica para generar los tableros
}

void testBench() {
    std::cout << "Ejecutando el test bench..." << std::endl;
    // Lógica para ejecutar el test bench
}
int main(int argc, char* argv[]) {
    int opt;
    bool flagG = false;
    bool flagT = false;
    int numTableros = 0;

    while ((opt = getopt(argc, argv, "gt")) != -1) {
        switch (opt) {
            case 'g':
                flagG = true;
                numTableros = std::stoi(optarg);
                break;
            case 't':
                flagT = true;
                break;
            case '?':
                cerr << "Uso: " << argv[0] << " [-g num_tableros] [-t]" << endl;
                return 1;
            default:
                cerr << "Error inesperado al analizar los argumentos" << endl;
                return 1;
        }
    }

    // Verificar qué acción tomar según los argumentos recibidos
    if (!flagG && !flagT && optind == argc - 1) {
        // No se recibió ningún argumento especial, pero se proporcionó el nombre del archivo de tablero
        cout << "Resolviendo el tablero normal..." << endl;
        tablero miTablero;
        coords misCoords;
        inicializarCoods(&misCoords);
        // Usar el argumento proporcionado como nombre del archivo de tablero
        if (inicializarTablero(&miTablero, argv[optind])) {
            if (resolverTablero(&miTablero, &misCoords)) {
                cout << "El tablero ha sido resuelto" << endl;
                imprimirTablero(&miTablero);
            } else {
                myError("El tablero no tiene solucion");
            }
        } else {
            myError("Error al inicializar el tablero");
        }
    } else if (flagG) {
        // Se recibió el argumento -g, generamos tableros
        genTableros(numTableros);
    } else if (flagT) {
        // Se recibió el argumento -t, ejecutamos el test bench
        testBench();
    } else {
        // Argumento inválido
        cerr << "Argumento inválido" << endl;
        return 1;
    }

    return 0;
}


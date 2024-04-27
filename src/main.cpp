#include <iostream>
#include <string>
#include <unistd.h>
#include "colocar.h"
#include "backtrack.h"
#include "gen.h"
using namespace std;

// Prototipos de funciones
void genTableros(int numTableros) {
    std::cout << "Generando " << numTableros << " tableros..." << std::endl;
}

void help() {
  cout << "Menu de ayuda del programa colocar, hecho por: Ivan Deza y David Hudrea.\n";
  cout << "Opciones: \n";
  cout << "\t-g <n>\t genera n tablerso aleatoriamente (todos con solucion) y los guarda en ficheros con nombre test<n>.\n";
  cout << "\t-t\t crea un comportamiento productor consumidor entre un hilo que crea tableros aleatoriamente y otros hilos que los resuelven (futuro)\n";
  cout << "si no recibimos ninguna opcion, se toma como primer parametro el nombre del fichero a resolver (modo normal que resuelve un tablero)\n";
  cout << "Abril 2024";
}

void banner() {
  std::cout << " ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓███████▓▒░  \n";
  std::cout << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░▒▓███████▓▒░  \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << " ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "                                                                                            \n";
  std::cout << "          De: Ivan Deza y David Hudrea                                                      \n";
  std::cout << std::endl;
}

void testBench() {
    std::cout << "Work in progress !" << std::endl;
}
int prueba(int argc, char* argv[]) {
    int opt;
    bool flagG = false;
    bool flagT = false;
    bool flagH = false;
    int numTableros = 0;

    while ((opt = getopt(argc, argv, "gth")) != -1) {
        switch (opt) {
            case 'g':
                info("caso g");
                flagG = true;
                //numTableros = std::stoi(optarg);
                break;
            case 't':
                flagT = true;
                break;
            case 'h':
                flagH = true;
                break;
            case '?':
                cerr << "Uso: " << argv[0] << " [filename] [-g num_tableros] [-t]" << endl;
                return 1;
            default:
                cerr << "Error inesperado al analizar los argumentos" << endl;
                return 1;
        }
    }

    // Verificar qué acción tomar según los argumentos recibidos
    if (!flagG && !flagT && optind == argc - 1) {
        // No se recibió ningún argumento especial, pero se proporcionó el nombre del archivo de tablero
        tablero miTablero;
        coords misCoords;
        // Usar el argumento proporcionado como nombre del archivo de tablero
        if (inicializarTablero(&miTablero, argv[optind])) {
            inicializarCoods(&misCoords, &miTablero);
            if (resolverTablero(&miTablero, &misCoords)) {
                imprimirTablero(&miTablero);
                liberarTablero(&miTablero);
            } else {
                liberarTablero(&miTablero);
                myError("El tablero no tiene solucion");
            }
        } else {
            myError("Error al inicializar el tablero");
        }
    } 
    else if (flagG) {
        int numT = 0;
        cout<<"Introduce el numero de tableros a generar: ";
        cin>>numT;
        info("Generando tableros...");
        for(int i = 1; i <= numT; i++) {
            generateFile(3, 3, i);
        }
        
    } 
    else if (flagT) {
        testBench();
    }
    else if(flagH) {
        banner();
        help();
        return 0;
    }
    else {
        banner();
        help();
        cerr << "\nArgumento inválido" << endl;
        return 1;
    }
    return 0;
}
int main(int argc, char* argv[]) {
    return prueba(argc, argv);
}

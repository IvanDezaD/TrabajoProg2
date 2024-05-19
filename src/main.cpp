/*
*  Ivan Deza: 837603
*  David Hudrea: 868573
*/ 
#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "colocar.h"
#include "backtrack.h"
#include "gen.h"
#include <signal.h>
using namespace std;

void ctrl_cHandler(int signum) {
  printf("\nCtrl_c detectado: %d, saliendo!", signum);
  printf("\033[?25h");
  exit(EXIT_FAILURE);
}

void help() {
  cout << "Menu de ayuda del programa colocar, hecho por: Ivan Deza y David Hudrea.\n";
  cout << "Opciones: \n";
  cout << "\t-g <n>\t genera n tablerso aleatoriamente (todos con solucion) y los guarda en ficheros con nombre test<n>.\n";
  cout << "\t-t\t crea un comportamiento productor consumidor entre un hilo que crea tableros aleatoriamente y otros hilos que los resuelven (futuro)\n";
  cout << "Si no recibimos ninguna opcion, se toma como primer parametro el nombre del fichero a resolver (modo normal que resuelve un tablero)\n";
  cout << "Abril 2024\n";
}

void banner() {
  std::cout << "\033[0;31m";
  std::cout << " ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓██████▓▒░ ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓███████▓▒░  \n";
  std::cout << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░▒▓███████▓▒░  \n";
  std::cout << "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << " ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓████████▓▒░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ \n";
  std::cout << "                                                                                            \n";
  std::cout << "\033[0m";
  std::cout << "          De: Ivan Deza y David Hudrea                                                      \n";
  std::cout << std::endl;
}

void testBench() {
    std::cout << "Work in progress !" << std::endl;
}
int arguments(int argc, char* argv[]) {
    int opt;
    bool flagG = false;
    bool flagT = false;
    bool flagH = false;
    int valor = 0;

    while ((opt = getopt(argc, argv, "g:th")) != -1) {
        switch (opt) {
            case 'g':
                info("caso g");
                flagG = true;
                valor = atoi(optarg);
                break;
            case 't':
                flagT = true;
                break;
            case 'h':
                flagH = true;
                break;
            case '?':
                help();
                cerr << "Uso: " << argv[0] << " [filename] [-g num_tableros] [-t]" << endl;
                return 1;
            default:
                cerr << "Error inesperado al analizar los argumentos" << endl;
                return 1;
        }
    }

    // Verificamos que accion hacer en caso de los parametros recibidos
    if (!flagG && !flagT && optind == argc - 1) {
        // No se recibió ningún argumento especial, pero se proporcionó el nombre del archivo de tablero
        tablero miTablero;
        // Usamos el argumento proporcionado como nombre del archivo de tablero
        if (inicializarTablero(&miTablero, argv[optind])) {
            if (resolverTablero(&miTablero)) {
                imprimirTablero(&miTablero);
                liberarTablero(&miTablero);
            } else {
                imprimirTablero(&miTablero);
                liberarTablero(&miTablero);
                myError("El tablero no tiene solucion");
            }
        } else {
            myError("Error al inicializar el tablero");
        }
    } 
    else if (flagG) {
        generarFicheros(valor);
        printf("Se generaron %d ficheros y se guardaron en la carpeta tests\n", valor);
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

//NOTE:Añadir criba (resolvemos filas en vez de casillas individuales)
int main(int argc, char* argv[]) {
  printf("\033[?25l"); //Quitamos el cursor
  //printf("\033[H\033[2J");
  signal(SIGINT, ctrl_cHandler); //Manejador de señales (ctrl_c)
  arguments(argc, argv);
  printf("\033[?25h");
  return 0;
}

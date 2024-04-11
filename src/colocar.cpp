#include "colocar.h"
#include "log.h"
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <iostream>

//el tamaño de matriz es 3x3 pero esta funcion nos la guardamos para cuando el tamaño sea dinamico (por si lo hacemos)
void reservarTablero(tablero *miTablero, int rows, int columns) {
  miTablero->rows = rows;
  miTablero->columns = columns;
  miTablero->tablero = (int**)malloc((rows+2)*sizeof(int*)); //necesitamos espacio para rows y 2 mas (las que nos indican cuantos edificios se ven)
  if(miTablero->tablero == NULL) {
    myError("Error reservando memoria para el tablero!");
  }

  for(int i = 0; i < rows; i++) {
    miTablero->tablero[i] = (int*)malloc((columns+2) * sizeof(int)); //Lo mismo para las columnas
    if(miTablero->tablero[i] == NULL) {
      myError("Error reservando memoria para las columnas del tablero!");
    }
  }
  okay("Tablero inicializado con exito.");
}

/*---Otra manera de hacer lo mismo pero con implementacion diferente---
void inicializarTablero2(tablero* miTablero, int rows, int columns) {
  miTablero->rows = rows;
  miTablero->columns = columns;
  miTablero->tablero = (int**)calloc(rows*columns, sizeof(int));
  if(miTablero->tablero == NULL) {
    warn("Error reservando memoria para el tablero!");
    exit(EXIT_FAILURE);
  }
}
*/

/*-----------LIBERAR MEMORIA------------*/
void liberarTablero(tablero* miTablero) {
  //Liberamos memoria de las columnas de cada fila
  for(int i = 0; i < (miTablero->rows + 2); i++) {
    free(miTablero->tablero[i]);
  }
  //Liberamos la memoria de cada fila
  free(miTablero->tablero);
}

void colocarValor(tablero *miTablero, int row, int column, int value) {
  info("Colocando altura: %d en las coordenadas: %d, %d", value, row, column);
  //Mandar error si intentamos acceder a una direccion fuera de rango!
  if(miTablero->rows<= row+1 || miTablero->columns <= column + 1) {
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  //Si la posicion es valida devolvemos su contenido
  miTablero->tablero[row+1][column+1] = value;
}

int valorEnCordenada(tablero *miTablero, int row, int column) {
  info("Obteniendo valor de las coordenadas : %d, %d", row, column);
  //Mandar error si intentamos acceder a una direccion de memoria fuera de rango (invalida, ya que hay mas direcciones validas que no son visibles)
  if(miTablero->rows + 1 < row + 1 || miTablero->columns + 1 < column + 1 || row < 1 || column < 1) {
     myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  return miTablero->tablero[row][column];
}

int getMaxRow(tablero* miTablero) {
  return miTablero->rows;
}

int getMaxcolumn(tablero* miTablero) {
  return miTablero->columns;
}

void leerFichero(tablero *miTablero, std::ifstream fichero) {
  if(!fichero.is_open()) {
    myError("El ifstream proporcionado no ha sido inicializado correctamente, stackTrace : %s", __FUNCTION__);
  }
}

//Imprimimos el tablero actual
void imprimirTablero(tablero *miTablero) {
  for(int i = 1; i < miTablero->rows+1; i++) {
    for(int j = 1; j < miTablero->columns+1; j++) {
     std::cout << miTablero->tablero[i][j];
    }
     std::cout << std::endl;
  }
}

//Para añadir un elemento nuevo al tablero se necesita usar siempre la funcion colocarValor, (buena praxis)
int tests(void) {
  tablero miTablero;
  reservarTablero(&miTablero, 5, 6);
  colocarValor(&miTablero, 6, 5, 7);
  int valor = miTablero.tablero[4][5];
  info("Valor obtenido : %d", valor);
  return 0;
}

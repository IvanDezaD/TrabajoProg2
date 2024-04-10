#include "colocar.h"
#include "log.h"
#include <cstdlib>
#include <stdlib.h>

//el tamaño de matriz es 3x3 pero esta funcion nos la guardamos para cuando el tamaño sea dinamico (por si lo hacemos)
void reservarTablero(tablero *miTablero, int rows, int columns) {
  miTablero->rows = rows;
  miTablero->columns = columns;
  miTablero->tablero = (int**)malloc(rows*sizeof(int*));
  if(miTablero->tablero == NULL) {
    myError("Error reservando memoria para el tablero!");
  }

  for(int i = 0; i < rows; i++) {
    miTablero->tablero[i] = (int*)malloc(columns * sizeof(int));
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

//Para liberar la memoria reservada para el tablero
void liberarTablero(tablero* miTablero) {
  //Liberamos memoria de las columnas de cada fila
  for(int i = 0; i < miTablero->rows; i++) {
    free(miTablero->tablero[i]);
  }
  //Liberamos la memoria de cada fila
  free(miTablero->tablero);
}

void colocarValor(tablero *miTablero, int row, int column, int value) {
  info("Colocando altura: %d en las coordenadas: %d, %d", value, row, column);
  if(miTablero->rows<= row || miTablero->columns <= column) {
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  miTablero->tablero[row][column] = value;
}

int getMaxRow(tablero* miTablero) {
  return miTablero->rows;
}

int getMaxcolumn(tablero* miTablero) {
  return miTablero->columns;
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

#include "log.h"
#include "colocar.h"
#include "backtrack.h"






//NOTE: importante destacar que en esta implementacion, el tamaño es NxM, pero en realidad la matriz de verdad es N+2xM+2 ya que tenemos los indicadores de alturas, pero esos posteriormente los ignoramos, sencillamente llamando a la funcion con un +1
bool resolverTablero(tablero *miTablero) {
  if ( estaResuelto(miTablero) ) {
    return true;
  }
  else {
    for (int i = 0; i < miTablero->rows; i++) {
      for (int j = 0; j < miTablero->columns; j++) {
        if (miTablero->tablero[i][j] == 0) {
          for (int k = 1; k <= miTablero->rows; k++) {
            if (esCorrecto(miTablero, i, j, k)) {
              miTablero->tablero[i][j] = k;
              if (resolverTablero(miTablero)) {
                return true;
              }
              else {
                miTablero->tablero[i][j] = 0;
              }
            }
          }
          return false;
        }
      }
    }
  }
  return false;
}

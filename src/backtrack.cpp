#include "log.h"
#include "colocar.h"
#include "backtrack.h"

//NOTE: importante destacar que en esta implementacion, el tamaño es NxM, pero en realidad la matriz de verdad es N+2xM+2 ya que tenemos los indicadores de alturas, pero esos posteriormente los ignoramos, sencillamente llamando a la funcion con un +1
bool resolverTablero(tablero *miTablero) {
  if (estaResuelto(miTablero)) {
    return true;
  }
  else {
    for(int i = 1; i < miTablero->rows+1; i++) {
      for(int j = 1; j < miTablero->columns+1; j++) {
        if(miTablero->tablero[i][j] == 0) {
          for(int k = 1; k < 5; k++) {
            colocarValor(miTablero, i, j, k);
            if(esCorrecto(miTablero, i, j, k)) {
              if(resolverTablero(miTablero)) {
                return true;
              }
            }
            colocarValor(miTablero, i, j, 0);
          }
          return false;
        }
      }
    }
  }
  return false;
}

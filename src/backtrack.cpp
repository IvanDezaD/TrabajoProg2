#include "colocar.h"
#include "backtrack.h"
#include <unistd.h>

//NOTE: importante destacar que en esta implementacion, el tamaño es NxM, pero en realidad la matriz de verdad es N+2xM+2 ya que tenemos los indicadores de alturas, pero esos posteriormente los ignoramos, sencillamente llamando a la funcion con un +1
bool resolverTablero(tablero *miTablero) {
  if (estaResuelto2(miTablero)) {
    return true;
  }
  else {
    for(int i = 1; i < miTablero->rows+1; i++) {
      for(int j = 1; j < miTablero->columns+1; j++) {
        if(miTablero->tablero[i][j] == 0) {
          info("Casilla vacia encontrada en i: %d, j: %d", i, j);
          for(int k = 1; k <= maxColumnOrRow(miTablero); k++) {
            colocarValor(miTablero, i, j, k);
            okay("Valor: %d colocado en i: %d, j: %d", k, i, j);
            if(esCorrecto2(miTablero, i, j)) {
              okay("El valor es correcto");
              if(resolverTablero(miTablero)) {
                return true;
              }
            }
            borrarMovimiento(miTablero, i, j);
          }
          return false;
        }
      }
    }
  }
  return false;
}

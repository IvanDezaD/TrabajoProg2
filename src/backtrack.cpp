#include "colocar.h"
#include "backtrack.h"

//NOTE: importante destacar que en esta implementacion, el tamaño es NxM, pero en realidad la matriz de verdad es N+2xM+2 ya que tenemos los indicadores de alturas, pero esos posteriormente los ignoramos, sencillamente llamando a la funcion con un +1
bool resolverTablero(tablero *miTablero, coords *misCoords) {
  //Queremos evitar esta comparacion todo el rato ya que es muy costosa en tiempo
  if (estaResuelto(miTablero)) {
    return true;
  }
  else {
    for(int i = 0; i < miTablero->rows+1; i++) {
      for(int j = 0; j < miTablero->columns+1; j++) {
        if(miTablero->tablero[i][j] == 0) {
          for(int k = 1; k <= maxColumnOrRow(miTablero); k++) {
            updateProgressBar("Resolviendo el tablero!\n");
            colocarValor(miTablero, i, j, k);
            imprimirTablero(miTablero);
            okay("Valor: %d colocado en i: %d, j: %d", k, i, j);
            if(esCorrecto(miTablero, i+1, i+1)) {
              info("El valor es correcto");
              if(resolverTablero(miTablero, misCoords)) {
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
  info("Saliendo 2");
  return false;
}

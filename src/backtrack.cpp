/*
*  Ivan Deza: 837603
*  David Hudrea: 868573
*/ 
#include "colocar.h"
#include "backtrack.h"
#include <unistd.h>

//NOTE: importante destacar que en esta implementacion, el tamaño es NxM, pero en realidad la matriz de verdad es N+2xM+2 ya que tenemos los indicadores de alturas, pero esos posteriormente los ignoramos, sencillamente llamando a la funcion con un +1
bool resolverTablero(tablero *miTablero) {
  if (estaResuelto2(miTablero)) {
    return true;
  }
  else {
    for(int i = 1; i < miTablero->rows+1; i++) { //Para cada fila
      for(int j = 1; j < miTablero->columns+1; j++) { //Para cada columna
        if(miTablero->tablero[i][j] == 0) { //Si la casilla esta vacia
          info("Casilla vacia encontrada en i: %d, j: %d", i, j);
          for(int k = 1; k <= maxColumnOrRow(miTablero); k++) { // Para cada movimiento posible
            colocarValor(miTablero, i, j, k); //Colocamos el valor en las coordenadas i, j
            //imprimirTablero(miTablero);
            okay("Valor: %d colocado en i: %d, j: %d", k, i, j); 
            if(esCorrecto2()) { //Antes esto cribaba opciones, lo he mantenido para que se pueda observar el intento
              okay("El valor es correcto");
              if(resolverTablero(miTablero)) { //Llamada recursiva
                return true;
              }
            }
            borrarMovimiento(miTablero, i, j); // Si salimos de la pila de llamadas es que ese movimiento no era valido
          }
          return false;
        }
      }
    }
  }
  return false;
}

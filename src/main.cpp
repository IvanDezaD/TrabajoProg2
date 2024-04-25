#include "backtrack.h"
#include "colocar.h"

//Funcion main del programa donde se opera toda la logica
int main(int argc, char* argv[]) {
  tests();
  tablero miTablero;
  inicializarTablero(&miTablero, "tests/test1.txt");
  coords misCoords;
  //resolverTablero(&miTablero, &misCoords);
}

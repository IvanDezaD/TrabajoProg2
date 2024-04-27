#include "gen.h"
#include "colocar.h"

#include <cstdlib>
#include <ctime>


int generateRandom(int min, int max) {
  int numero = rand() % (max - min + 1) + min;

  return numero;
}

void guardarTablero(tablero *miTablero, std::string nombreArchivo){
    std::ofstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo.is_open()){
        std::cout << "Error al abrir el archivo" << std::endl;
        return;
    }
    else{
        for(int i = 0; i <= miTablero->rows+1; i++){
            for(int j = 0; j <= miTablero->columns+1; j++){
                archivo << miTablero->tablero[i][j] << " ";
            }
            archivo << std::endl;
        }
    }
    archivo.close();
}

void generateFile(int rows, int columns) {
  srand(time(nullptr));
  info("Generando archivo de tablero");
  info("rows: %d columns: %d", rows, columns);
  tablero miTablero;
  construirTablero(&miTablero, rows+2, columns+2);
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= columns; j++) {
      int maxRowsOrColumns = maxColumnOrRow(&miTablero);
      int valor = generateRandom(1, maxRowsOrColumns);
      info("Valor = %d", valor);
      miTablero.tablero[i][j] = valor;
    }
  }
  for(int i = 0; i <= rows+1; i++) {
    for(int j = 0; j <= columns+1; j++) {
      if(i == 0 || j == 0 || i == rows+1 || j == columns+1) {
        miTablero.tablero[i][j] = cuantosVeo(&miTablero, i, j);
      }
    }
  }
  for(int i = 1; i <= rows; i++) {
    for(int j = 1; j <= columns; j++) {
      miTablero.tablero[i][j] = 0;
    }
  }
  imprimirTablero(&miTablero);
  std::string nombreArchivo = "test1.txt";
  guardarTablero(&miTablero, nombreArchivo);

}



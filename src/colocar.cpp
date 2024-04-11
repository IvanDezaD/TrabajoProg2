/*
 *  Fichero que contiene la impementacion de las funciones definidas en colocar.h
 *  Por Ivan Deza y David Hudrea
 * 
 */
#include "colocar.h"

//el tamaño de matriz es 3x3 pero esta funcion nos la guardamos para cuando el tamaño sea dinamico (por si lo hacemos)
void construirTablero(tablero *miTablero, int rows, int columns) {
  info("Construyendo tablero de : %d filas y: %d columnas", rows-2, columns-2);
  miTablero->rows = rows-2;
  miTablero->columns = columns-2;
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

void inicializarTablero(tablero *miTablero, std::string fichero) {
  info("Inicializando el tablero!");
  
  std::ifstream myFile;
  myFile.open(fichero);
  int filas = 0;
  int columnas = 0;
  char token;
  
  if(!myFile.is_open()) {
    myError("El ifstream proporcionado no ha sido inicializado correctamente, stackTrace : %s", __FUNCTION__);
  }
  
  okay("Fichero %s abierto con exito!", fichero.c_str());
  std::string linea;
  
  //WARN: Deberiamos cambiar esta funcion por algo mejor
  while(getline(myFile, linea, '\n')) {
    std::istringstream iss(linea);
    if(filas == 0) {
      while(iss >> token) {
        columnas++;
      }  
    }
    filas++;
  }
  myFile.clear();
  myFile.seekg(0, std::ios::beg);
  construirTablero(miTablero, filas, columnas);
  //Leemos todas las líneas;
  int fila = 0;
  while (getline(myFile, linea, '\n')) {
    std::istringstream iss(linea);
    int columna = 0;
    //Para recorrer todas las columnas de la fila (hasta que no haya mas)
    while(iss >> token) {
      //Aqui no podemos usar la funcion colocar valor, ya que por construccion esta diseñada para no poder acceder a elementos 
      //no sean parte del tablero a resolver (lo que inicialmente son 0s).
      miTablero->tablero[fila][columna] = atoi(&token);
      columna++;
    }
    columna = 0;
    fila++;
  }
}

//Imprimimos el tablero actual
void imprimirTablero(tablero *miTablero) {
  for(int i = 1; i < miTablero->rows+1; i++) {
    for(int j = 1; j < miTablero->columns+1; j++) {
     std::cout << miTablero->tablero[i][j] << " ";
    }
     std::cout << std::endl;
  }
}

//Para añadir un elemento nuevo al tablero se necesita usar siempre la funcion colocarValor, (buena praxis)
void tests(void) {
  printf("Iniciando tests");
  tablero miTablero;
  inicializarTablero(&miTablero, "tests/test1.txt");
  imprimirTablero(&miTablero);
}

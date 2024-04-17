/*
 *  Fichero que contiene la implementacion de las funciones definidas en colocar.h
 *  Por Ivan Deza y David Hudrea
 *  13 Apr 2024
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

/*---------------------------COLOCAMOS VALOR EN COORDENADAS----------------------------*/
void colocarValor(tablero *miTablero, int row, int column, int value) {
  info("Colocando altura: %d en las coordenadas: %d, %d", value, row, column);
  //Mandar error si intentamos acceder a una direccion fuera de rango!
  if(miTablero->rows<= row+1 || miTablero->columns <= column + 1) {
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  //Si la posicion es valida devolvemos su contenido
  miTablero->tablero[row+1][column+1] = value;
}

/*--------------------QUE VALOR HAY EN LAS COORDENADAS ESPECIFICADAS--------------------*/
int valorEnCordenada(tablero *miTablero, int row, int column) {
  info("Obteniendo valor de las coordenadas : %d, %d", row, column);
  //Mandar error si intentamos acceder a una direccion de memoria fuera de rango (invalida, ya que hay mas direcciones validas que no son visibles)
  //if(miTablero->rows + 1 < row + 1 || miTablero->columns + 1 < column + 1 || row < 1 || column < 1) {
  //   myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  //}
  return miTablero->tablero[row][column];
}

/*--------NUMERO DE FILAS--------*/
int getMaxRow(tablero* miTablero) {
  return miTablero->rows;
}

/*---------NUMERO DE COLUMNAS--------*/
int getMaxcolumn(tablero* miTablero) {
  return miTablero->columns;
}

//NOTE: Podríamos dividir esto en 2 funciones diferentes y pasar el ifstream de una a otra.
/*-------------------INICIALIZAMOS EL TABLERO--------------------*/
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

/*----------IMPRIMIMOS EL TABLERO----------*/
void imprimirTablero(tablero *miTablero) {
  for(int i = 1; i < miTablero->rows+1; i++) {
    for(int j = 1; j < miTablero->columns+1; j++) {
     std::cout << miTablero->tablero[i][j] << " ";
    }
     std::cout << std::endl;
  }
}

int cuantosVeoIzda(int vector[], int size) {
  info("Izda!");
  int maximo = vector[1];
  int veo = 1;
  for(int i = 1; i <= size; i++) {
    if(vector[i] > maximo) {
      maximo = vector[i];
      veo = i;
      if(i < size && vector[i] > vector[i+1]) {
        return veo;
      }
    }
  }
  return veo;
}

int cuantosVeoDcha(int vector[], int size) {
  info("Dcha!");
  int max = vector[size];
  int veo = 1;
  for(int i = vector[size-1]; i >= 0; i--) {
    if(vector[i] > max) {
      max = vector[i];
      veo++;
      if(i < size && vector[i] > vector[i+1]) {
        return veo;
      }
    }
  }
  return veo;
}

int cuantosVeoSuperior(tablero *miTablero, int column) {
  info("Superior!");
  int max = miTablero->tablero[1][column];
  int veo = 1;
  for(int i = 1; i <= miTablero->rows; i++) {
    if(miTablero->tablero[i][column] > max) {
      max = miTablero->tablero[i][column];
      veo = i;
      if(i < miTablero->rows && miTablero->tablero[i][column] > miTablero->tablero[i+1][column]) {
        return veo;
      }
    }
  }
  return veo;
}

int cuantosVeoInferior(tablero *miTablero, int column) {
  info("Inferior!");
  int max = miTablero->tablero[miTablero->rows][column];
  int veo = 1;
  for(int i = miTablero->rows-1; i >= 0; i--) {
    if(miTablero->tablero[i][0] > max) {
      max = miTablero->tablero[i][column];
      veo++;
      if(i < miTablero->rows && miTablero->tablero[i][column] > miTablero->tablero[i+1][column]) {
        return veo;
      }
    }
  }
  return veo;
}

//TODO:Añadir sanitizacion de entrada y loguear errores
//NOTE: Con las coordenadas sacar la direccion(cual de las 4 posibles funciones usar)
int cuantosVeo(tablero *miTablero, int row, int column) {
  info("Calculando cuantos veo desde la posición %d, %d!", row, column);
  if(row == 0) {
    return cuantosVeoSuperior(miTablero, column);
  }
  //Si no es 0, deberia ser columnas
  else if(row == miTablero->rows+1) {
    return cuantosVeoInferior(miTablero, column);
  }
  if(column == 0) {
    return cuantosVeoIzda(miTablero->tablero[row], miTablero->columns);
  }
  else if(column == miTablero->columns+1) {
  return cuantosVeoDcha(miTablero->tablero[row], miTablero->columns);
  }
  //Es un error;
  return -1;
}

//NOTE: Añadir logica para que si la fila o columna esta completa, devuelva true
bool filaCompleta(tablero *miTablero, int row) {
  info("Comprobando si la fila esta llena");
  return miTablero->tablero[miTablero->columns+1][row] != 0;
}

//NOTE: Añadir logica para que si la fila o columna esta completa, devuelva true
bool columnaCompleta(tablero *miTablero, int column) {
  return miTablero->tablero[miTablero->rows+1][column] != 0;
} 


bool esCorrecto(tablero *miTablero, int row, int column, int value) {
  //Convertir de coordenadas a puntos que verificar.
  //NOTE: Si es la ultima fila o la ultima columna devolvemos true si y solo si, el numero que veo es IGUAL al especificado
  info("Calculando si el haber puesto: %d en %d, %d permite seguir resolviendo el tablero!", value, row, column);
  int top = cuantosVeo(miTablero, 0, column);
  int bottom = cuantosVeo(miTablero, miTablero->rows+1, column);
  int left = cuantosVeo(miTablero, row, 0);
  int right = cuantosVeo(miTablero, row, miTablero->columns+1);
  if (!filaCompleta(miTablero, row) || !columnaCompleta(miTablero, column)) {
    if(top <=valorEnCordenada(miTablero, 0, column) && bottom <= valorEnCordenada(miTablero, miTablero->rows+1, column) && left <= valorEnCordenada(miTablero, row, 0) && right <= valorEnCordenada(miTablero, row, miTablero->columns+1)) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if(top == valorEnCordenada(miTablero, 0, column) && bottom == valorEnCordenada(miTablero, miTablero->rows+1, column) && left == valorEnCordenada(miTablero, row, 0) && right == valorEnCordenada(miTablero, row, miTablero->columns+1)) {
      return true;
    }
    else {
      info("No es valido el movimiento!");
      return false;
    }
  }
}
bool estaResuelto(tablero *miTablero){
  for(int i = 1; i < miTablero->rows+1; i++) {
    for(int j = 1; j < miTablero->columns+1; j++) {
      if(!esCorrecto(miTablero, i, j, miTablero->tablero[i][j])) {
        return false;
      }
    }
  }
  return true;
}

  
//TODO:probar a fondo las funciones cuantasVeo
//Para añadir un elemento nuevo al tablero se necesita usar siempre la funcion colocarValor, (buena praxis)
void tests(void) {
  info("Iniciando tests!");
  tablero miTablero;
  inicializarTablero(&miTablero, "tests/test2.txt");
  if(esCorrecto(&miTablero, 4, 1, 4) && esCorrecto(&miTablero, 1, 4, 1) && esCorrecto(&miTablero, 2, 2, 4)) {
    okay("La funcion valido correctamente");
  }
  int veo = cuantosVeo(&miTablero, 0, 2);
  info("Se ven: %d", veo);
  imprimirTablero(&miTablero);
}

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

void inicializarCoods(coords *misCoords, tablero* miTablero) {
  misCoords->north = 0;
  misCoords->south = miTablero->rows+1;
  misCoords->east = 0;
  misCoords->west = miTablero->columns+1;
  okay("Coordenadas de lectura inicializadas correctamente!");
}

/*---------------------------COLOCAMOS VALOR EN COORDENADAS----------------------------*/
void colocarValor(tablero *miTablero, int row, int column, int value) {
  info("Colocando altura: %d en las coordenadas: %d, %d", value, row, column);
  //Mandar error si intentamos acceder a una direccion fuera de rango!
  if(miTablero->rows <= row+1 || miTablero->columns <= column+1 || row < 0 || column < 0) {
    liberarTablero(miTablero); //Si falla deberemos liberar la memoria antes de salir para evitar memory leaks
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  //Si la posicion es valida devolvemos su contenido
  miTablero->tablero[row+1][column+1] = value;
}

/*--------------------QUE VALOR HAY EN LAS COORDENADAS ESPECIFICADAS--------------------*/
int valorEnCordenada(tablero *miTablero, int row, int column) {
  info("Obteniendo valor de las coordenadas : %d, %d", row, column);
  //Mandar error si intentamos acceder a una direccion de memoria fuera de rango (invalida, ya que hay mas direcciones validas que no son visibles)
  if(miTablero->rows <= row+1 || miTablero->columns <= column+1 || row < 0 || column < 0) {
     myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  return miTablero->tablero[row+1][column+1];
}

/*------------HEIGHT AT COORDINATE (EXTERIOR)------------*/
int getHeightAt(tablero* miTablero, int row, int column) {
// Devuelve error si intentamos acceder a una direccion de memoria no valida o a las direcciones que hacen esquina,es decir
// las que no son parte del tablero a resolver como por ejemplo miTablero->tablero[0][0] o miTablero->tablero[miTablero->rows+1][miTablero->columns+1]
// Si es una dirección exterior valida, devolvemos su contenido
if(((row == 0 || row == miTablero->rows+1) && (column!=0 || column!=miTablero->columns+1)) ||((column == 0 || column == miTablero->columns+1) &&(row!=0 || row!=miTablero->rows+1))) {
    return miTablero->tablero[row][column];
  
  }
  else {
    myError("Intentando acceder a una posicion no valida en la funcion : %s", __FUNCTION__);
  }
}

/*--------NUMERO DE FILAS--------*/
int getMaxRow(tablero* miTablero) {
  return miTablero->rows;
}

/*---------NUMERO DE COLUMNAS--------*/
int getMaxcolumn(tablero* miTablero) {
  return miTablero->columns;
}

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

/*--------------CUANTOS VEMOS---------------*/
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


/*-----------CUANTAS VEO DESDE X POSICION EXTERIOR---------------*/
int cuantosVeo(tablero *miTablero, int row, int column) {
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

/*---------------ESTA COMPLETA LA FILA-----------------------*/
bool filaCompleta(tablero *miTablero, int row) {
  return miTablero->tablero[miTablero->columns+1][row] != 0;
}

/*-------------ESTA COMPLETA LA COLUMNA------------------*/
bool columnaCompleta(tablero *miTablero, int column) {
  return miTablero->tablero[miTablero->rows+1][column] != 0;
} 


bool esCorrecto(tablero *miTablero, int row, int column) {
  //Convertir de coordenadas a puntos que verificar.
  info("Calculando si el movimiento en: %d, %d permite seguir resolviendo el tablero!", row, column);
  //Variables auxiliares por razones de legibilidad (se podrian usar #define pero al tratarse de memDinamica no).
  const int north = 0;
  const int south = miTablero->rows+1;
  const int east  = 0;
  const int west  = miTablero->columns+1;

  int top = cuantosVeo(miTablero, north, column);
  int bottom = cuantosVeo(miTablero, south , column);
  int left = cuantosVeo(miTablero, row, east);
  int right = cuantosVeo(miTablero, row, west);

  if (!filaCompleta(miTablero, row) || !columnaCompleta(miTablero, column)) {
    if(top <= getHeightAt(miTablero, north, column) && bottom <= getHeightAt(miTablero, south, column) && left <= getHeightAt(miTablero, row, east) && right <= getHeightAt(miTablero, row, west)) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if(top == getHeightAt(miTablero, north, column) && bottom == getHeightAt(miTablero, south, column) && left == getHeightAt(miTablero, row, east) && right == getHeightAt(miTablero, row, west)) {
      return true;
    }
    else {
      info("El movimiento no es válido!");
      return false;
    }
  }
}

/*---------------TABLERO RESUELTO?-----------*/
bool estaResuelto(tablero *miTablero){
  for(int i = 1; i < miTablero->rows+1; i++) {
    for(int j = 1; j < miTablero->columns+1; j++) {
      if(miTablero->tablero[i] == 0) {
        return false;
      }
    }
  }
  return true;
}

/*--------------------BORRAMOS EL MOVIMIENTO-------------------*/
void borrarMovimiento(tablero* miTablero, int row, int column) {
  miTablero->tablero[row][column] = 0;
}

/*-------------MAX ROW OR COLUMN------------*/
int maxColumnOrRow(tablero* miTablero) {
  if(miTablero->columns > miTablero->rows) {
    return miTablero->columns;
  }
  else {
    return miTablero->rows;
  }
}

//TODO:probar a fondo las funciones cuantasVeo
//Para añadir un elemento nuevo al tablero se necesita usar siempre la funcion colocarValor, (buena praxis)
void tests(void) {
  info("Iniciando tests!");
  tablero miTablero;
  inicializarTablero(&miTablero, "tests/test2.txt");
  if(esCorrecto(&miTablero, 4, 1)) {//&& esCorrecto(&miTablero, 1, 4) && esCorrecto(&miTablero, 2, 2)) {
    okay("La funcion valido correctamente");
  }
  int veo = cuantosVeo(&miTablero, 0, 2);
  info("Se ven: %d", veo);
  imprimirTablero(&miTablero);
}

/*
 *  Fichero que contiene la implementacion de las funciones definidas en colocar.h
 *  Por Ivan Deza y David Hudrea
 *  13 Apr 2024
 * 
 */
#include "colocar.h"
#include "log.h"

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
}

/*---------------------------COLOCAMOS VALOR EN COORDENADAS----------------------------*/
void colocarValor(tablero *miTablero, int row, int column, int value) {
  //Mandar error si intentamos acceder a una direccion fuera de rango!
  if(miTablero->rows <= row+1 || miTablero->columns <= column+1 || row < 0 || column < 0) {
    liberarTablero(miTablero); //Si falla deberemos liberar la memoria antes de salir para evitar memory leaks
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  //Si la posicion es valida devolvemos su contenido
  info("Colocando valor: %d en %d, %d", value, row+1, column+1)
  miTablero->tablero[row+1][column+1] = value;
}

/*--------------------QUE VALOR HAY EN LAS COORDENADAS ESPECIFICADAS--------------------*/
int valorEnCordenada(tablero *miTablero, int row, int column) {
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
int cuantosVeoIz(tablero* miTablero, int row) {
  int max = 0;
  int veo = 0;
  for(int i = 1; i <= miTablero->columns; i++) {
    if(miTablero->tablero[row][i] != 0) {
      if(miTablero->tablero[row][i] > max) {
        max = miTablero->tablero[row][i];
        veo++;
      }
      if(miTablero->tablero[row][i] > miTablero->tablero[row][i+1] && i < miTablero->columns) {
        return veo;
      }
    }
  }
  return veo;
}

int cuantosVeoDc(tablero* miTablero, int row) {
  int  max = 0;
  int veo = 0;
  for(int i = miTablero->columns; i > 0; i--) {
    if(miTablero->tablero[row][i] != 0) {
      if(miTablero->tablero[row][i] > max) {
        max = miTablero->tablero[row][i];
        veo++;
      }
      if(miTablero->tablero[row][i] > miTablero->tablero[row][i-1] && i > 1){
        return veo;
      }
    }
  }
  return veo;
}

int cuantosVeoSuperior(tablero* miTablero, int column) {
  int max = 0;
  int veo = 0;
  for(int i = 1; i <= miTablero->rows; i++) {
    if(miTablero->tablero[i][column] != 0) {
      if(miTablero->tablero[i][column] > max) {
        max = miTablero->tablero[i][column];
        veo++;
      }
      //if(miTablero->tablero[i][column] > miTablero->tablero[i+1][column] && i < miTablero->rows) {
        //return veo;
      //}
    }
  }
  return veo;
}

int cuantosVeoInferior(tablero* miTablero, int column) {
  int  max = 0;
  int veo = 0;
  for(int i = miTablero->rows; i > 0; i--) {
    if(miTablero->tablero[i][column] != 0) {
      if(miTablero->tablero[i][column] > max) {
        max = miTablero->tablero[i][column];
        veo++;
      }
      if(miTablero->tablero[i][column] > miTablero->tablero[i-1][column] && i > 1){
        return veo;
      }
    }
  }
  return veo;
}

//NOTE:FIX THIS SHIT
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
    return cuantosVeoIz(miTablero, row);
  }
  else if(column == miTablero->columns+1) {
  return cuantosVeoDc(miTablero, row);
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
  //Variables auxiliares por razones de legibilidad (se podrian usar #define pero al tratarse de memDinamica no).
  const int north = 0;
  const int south = miTablero->rows+1;
  const int west  = 0;
  const int east  = miTablero->columns+1;

  int top = cuantosVeo(miTablero, north, column);
  int bottom = cuantosVeo(miTablero, south , column);
  int left = cuantosVeo(miTablero, row, west);
  int right = cuantosVeo(miTablero, row, east);

  info("top: %d,bottom: %d, left: %d, right: %d ", top, bottom, left, right);

  if (!filaCompleta(miTablero, row) || !columnaCompleta(miTablero, column)) {
    if(top <= getHeightAt(miTablero, north, column) && bottom <= getHeightAt(miTablero, south, column) && left <= getHeightAt(miTablero, row, west) && right <= getHeightAt(miTablero, row, east)) {
      return true;
    }
    else {
      info("False1");
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
      if(miTablero->tablero[i][j] == 0) {
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

void updateProgressBar(const char* msg) {
    static const char animation[] = {'>', '=', '=', '=', '=', '=', '=', '='};
    static int index = 0;
    printf("\r\033[1;34m[%c%c%c%c%c%c%c%c]\033[0m %s", animation[index], animation[(index + 7) % 8], animation[(index + 6) % 8], animation[(index + 5) % 8], animation[(index + 4) % 8], animation[(index + 3) % 8], animation[(index + 2) % 8], animation[(index + 1) % 8], msg);
    fflush(stdout);
    index = (index + 1) % 8;
}

//TODO:probar a fondo las funciones cuantasVeo
//Para añadir un elemento nuevo al tablero se necesita usar siempre la funcion colocarValor, (buena praxis)
void tests(void) {
  info("Iniciando tests!");
  tablero miTablero;
  coords misCoords;
  inicializarTablero(&miTablero, "tests/test1.txt");
  inicializarCoods(&misCoords,&miTablero);
  info("Test 1 de esCorrecto: 3,1 -> valor esperado True");
  if(esCorrecto(&miTablero,3, 1)){
    okay("Test 1 de esCorrecto pasado!");
  }
  info("Test 2 de esCorrecto: 2,3->valor esperado: false");
  if(!esCorrecto(&miTablero, 2, 3)) {
    okay("Test 2 de esCorrecto pasado!");
  }
  info("Test 3 de esCorrecto: 1,2->valor esperado: True");
  if(esCorrecto(&miTablero, 1, 2)) {
    okay("Test 3 de la funcion es correcto pasada");
  }
  info("Test 4 de la funcion esCorreco: 3,3-> valor esperado: False");
  if(!esCorrecto(&miTablero, 3, 3)) {
    okay("Test 4 de la cuncion esCorrecto pasada con exito!");
  }
  imprimirTablero(&miTablero);
}

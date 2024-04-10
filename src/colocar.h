#pragma once
#include <string>

/*----Nuestra estructura tablero-----*/
typedef struct {
  int rows;
  int columns;
  int** tablero; //muy posiblemente esto no sea necesario
} tablero;

//Recibimos como parametro un tablero, y ponemos todas sus casillas a 0 (buena praxis)
void reservarTablero(tablero *miTablero, int rows, int columns);

//Recibimos las coordenadas de una casilla y colocamos el valor recibido. Validamos que las coordenadas son de indices correctos antes de nada
void colocarValor(tablero *miTablero, int row, int column,int value);

//Recibimos coordenadas y devolvemos cuantos edificios vemos desde esa coordenada (para este caso importante validar que las coordenadas son correctas)
int cuantosVeo(tablero miTablero, int row, int column);

//Recibimos el tablero y unas coordenadas y devolvemos la altura de esa manzana
int valorEnCordenada(tablero *miTablero, int row, int column); //return miTablero->tablero[row][column]

//Recibimos un tablero y liberamos el espacio reservado
void liberarTablero(tablero *miTablero);

//Recibimos el tablero y ponemos las casillas inicialmente con los valores del fichero!!
void inicializarTablero(tablero *miTablero, std::string fichero);

//Leemos y cargamos en la memoria el tablero leido del fichero.
void leerFichero(tablero *miTablero, std::string fichero);

//Recibimos el tablero y devolvemos el tamaño de columnas que tiene
int getMaxColumn(tablero *miTablero);

//Recibimos el tablero y devolvemos el maximo numero de filas
int getMaxRows(tablero *miTablero);

//Recibimos el tablero y lo imprimimos en pantalla
void imprimirTablero(tablero *miTablero);

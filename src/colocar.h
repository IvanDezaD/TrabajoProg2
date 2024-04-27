#pragma once
#pragma GCC optimize("O2")
#include "colocar.h"
#include "log.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

//TODO: quedan por hacer las especificaciones formales.
//TODO: revisar funciones
//TODO: quedan por implementar: estaResuelto(redundante pero para verificar) y esCorrecto. 

/*----Nuestra estructura tablero-----*/
typedef struct {
  int rows;
  int columns;
  int** tablero; //muy posiblemente esto no sea necesario
} tablero;

typedef struct {
  int north;
  int south;
  int east;
  int west;
} coords;

/*
 * Pre:  recibimos un tablero sin inicializar, ademas del numero de filas y columnas totales que vamos a necesitar para el tablero.
 * Post: se asigna a la estructura del tablero las columnas y filas correctas (las filas y columnas de la matriz a resolver, no la que contiene tambien el perimetro de alturas necesarias).
 *       se reserva espacio de memoria en el heap para el tablero dado el tamaño especificado. Ej: si recibimos 5 rows y 5 columns: el tablero a resolver sera de dimensiones 3x3 y se reservara espacio en el 
 *       heap para una matriz 5x5 (la que contiene la matriz a resolver ademas del perimetro)
 */
void construirTablero(tablero *miTablero, int rows, int columns);


/*
 * Pre:  recibimos un puntero a un tablero, una fila y una columna, ademas de un valor. Estos valores deben de estar dentro de los rangos definidos de la matriz.
 * Post: se asignara a la matriz del tablero(miTablero->tablero) en las coordenadas fila, columna, el valor definido: value -> miTablero->tablero[row][column] = value;
 */
void colocarValor(tablero *miTablero, int row, int column,int value);

/*
 * Pre:  recimos la estructura coords ademas de un tablero ya inicalizado.
 * Post: se asigna a la estructura los valores correctos para las coordenadas exteriores(el perimetro donde estan las alturas definidas que se deberan cumplir).
 *       ej: misCoords->north = 0
 *           misCoords->south = miTablero->rows+1
 *           misCoords->east = 0
 *           misCoords->west = miTablero->columns+1
 */
void inicializarCoods(coords *misCoords, tablero* miTablero);


/*
 * Pre: recibimos un tablero inicializado y parcialmente resuelto, ademas recibimos las coordenadas de un punto: row, column.
 * Post: cuantosVeo(miTablero, row, column) = cuantos edificios somos capaces de ver desde la posicion row, y column(siendo row o column un valor dentro de nuestra estructura coordenadas)
 *       esta funcion ya de por si sabe si es izquierda, derecha arriba o abajo y es capaz de determinar en que sentido ha de hacer la comprobacion.
 */
int cuantosVeo(tablero *miTablero, int row, int column);


/*
 * Pre:  recibimos el puntero a un tablero ya inicializado, en el cual se acaba de poner una altura nueva en la posicion: row, column
 * Post: devolveremos true si, y solo si el movimiento que acabamos de hacer permite seguir resolviendo el tablero(si se siguen cumpliendo las normas establecidas).
 */
bool esCorrecto(tablero* miTablero, int row, int column);


/*
 * Pre:  recibimos un puntero a un tablero 
 * Post: devolveremos true si y solo si el tablero ya se ha terminado de resolver y esta correctamente resuelto (por construccion esto ocurre si el tablero esta lleno ya que antes)
 *       de efectuar cada movimiento ya se comprueba si es valido o no.
 *
 */
bool estaResuelto(tablero *miTablero);

/*
 * Pre:  recibimos el puntero a un tablero, ademas de unas cordenadas row, column.
 * Post: valorEnCoordenada(miTablero, row, column) = el valor que se encuentra en la matriz en las coordenadas, row, column: ej: miTablero->tablero[row][column]
 *       NOTE: cabe destacar que esta funcion es usada solo para acceder a la matriz a resolver, no al perimetro que contiene las alturas definidas finales.
 *
 */
int valorEnCordenada(tablero *miTablero, int row, int column); //return miTablero->tablero[row][column]

/*
 * Pre:  recibimos el puntero a un tablero inicializado.
 * Post: liberaremos la memoria ocupada por la matriz de el tablero (para evitar memory leaks)!
 */
void liberarTablero(tablero *miTablero);

/*
 * Pre:  recibimos una cadena que contiene el nombre de un fichero ademas del puntero a un tablero NO inicializado.
 * Post: incializara tanto los valores de la estructura (rows, columns) como la matriz, con los valores leidos del fichero.
 */
bool inicializarTablero(tablero *miTablero, std::string fichero);

/*
 * Pre:  recibimos un puntero a un tablero ya inicializado.
 * Post: getMaxColumns(miTablero) = numero de columnas que tiene el tablero
 */
int getMaxColumn(tablero *miTablero);

/*
 * Pre:  recibimos un puntero a un tablero ya inicializado.
 * Post: getMaxRows(miTablero) = numero de filas que tiene el tablero.
 */
int getMaxRows(tablero *miTablero);

/*
 * Pre: recibimos un puntero a un tablero ya inicializado
 * Post: se muestra por pantalla el tablero
 */
void imprimirTablero(tablero *miTablero);

/*
 * Pre: recibimos una cadena
 * Post: actualizamos la barra de carga ([===>===] <msg> ->[=====>==] <msg>) da sensacion de movimiento
 */
void updateProgressBar(const char* msg);

/*
 * Pre: recibimos el puntero a un tablero ya inicializado
 * Post: maxColumnOrRow(miTablero) = el maximo valor que sea de columnas o filas, si hay mas filas devuelve el numero de filas y lo mismo en viceversa.
 */
int maxColumnOrRow(tablero* miTablero);

/*
 * Pre:  recibimos el puntero a un tablero en el cual se ha hecho un movimiento en la posicion row, column.
 * Post: insertamos un 0 en estas coordenadas(el equivalente a haber deshecho el movimiento!)
 */
void borrarMovimiento(tablero* miTablero, int row, int column);

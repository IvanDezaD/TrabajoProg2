#pragma once
#pragma GCC optimize("O3")
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

//Recibimos como parametro un tablero, y ponemos todas sus casillas a 0 (buena praxis)
void construirTablero(tablero *miTablero, int rows, int columns);

//Recibimos las coordenadas de una casilla y colocamos el valor recibido. Validamos que las coordenadas son de indices correctos antes de nada
void colocarValor(tablero *miTablero, int row, int column,int value);

//
void inicializarCoods(coords *misCoords);

//Recibimos coordenadas y devolvemos cuantos edificios vemos desde esa coordenada (para este caso importante validar que las coordenadas son correctas)
int cuantosVeo(tablero miTablero, int row, int column);

//recibimos el tablero y la casilla que acabamos de colocar y devolvemos true si y solo si el movimiento ha sido valido (no fastidia lo de las alturas).
bool esCorrecto(tablero* miTablero, int row, int column);

//Recibimos un tablero, y devolvemos si esta resuelto o no.
bool estaResuelto(tablero *miTablero);

//Recibimos el tablero y unas coordenadas y devolvemos la altura de esa manzana
int valorEnCordenada(tablero *miTablero, int row, int column); //return miTablero->tablero[row][column]

//Recibimos un tablero y liberamos el espacio reservado
void liberarTablero(tablero *miTablero);

//Recibimos el tablero y ponemos las casillas inicialmente con los valores del fichero!!
void inicializarTablero(tablero *miTablero, std::string fichero);

//Recibimos el tablero y devolvemos el numero de columnas que tiene.
int getMaxColumn(tablero *miTablero);

//Recibimos el tablero y devolvemos el numero de filas que tiene
int getMaxRows(tablero *miTablero);

//Recibimos el tablero y lo imprimimos en pantalla
void imprimirTablero(tablero *miTablero);

//funcion para podere hacer pruebas de desarrollo
void tests(void);

//Funcion usada par a mostrar una barra de carga por pantalla: [===>=]msg
void updateProgressBar(const char* msg);

//Para saber si hay mas columnas o filas
int maxColumnOrRow(tablero* miTablero);

void borrarMovimiento(tablero* miTablero, int row, int column);

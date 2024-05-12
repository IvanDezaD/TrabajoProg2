# TrabajoProg2
Repositorio del trabajo de la asignatura programacion 2 del segundo semestre
## Objetivos principales
Nuestro objetivo principal es hacer un programa que sea capaz de resolver el siguiente problema:
- Siendo que se entrega un fichero con el siguiente formato: 
```
x 1 2 3 x
2 0 0 0 1
1 0 0 0 2
2 0 0 0 1
x 1 2 3 x
```
Los 0s representan manzanas de una ciudad, y el valor de cada dígito (cada 0) es la altura de un edificio.
Los numeros que rodean el cuadrado de 3x3 en este caso. Es el numero de edificios que se deberia de poder ver desde esa posicion, por ejemplo:
Si el edifico en 0,0 es 1 y el de 0,1 es 2, pero el de la 0,2 es 1, se veran 2, ya que el segundo, con altura 2, tapa el tercero, que tiene altura 1.
### Ventajas
En esta implementacion buscamos que seamos capaces de resolver este problema para un tablero de NxM, siendo N y M los valores leidos en la cabecera del programa.
Para ello debemos implementar una memoria dinámica, para poder reservar el espacio de manera justa para poder usar la matriz.
Para hacer esto he recurrido a la siguiente funcion:
```c
void reservarTablero(tablero *miTablero, int rows, int columns) {
  miTablero->rows = rows;
  miTablero->columns = columns;
  miTablero->tablero = (int**)malloc(rows*sizeof(int*));
  if(miTablero->tablero == NULL) {
    myError("Error reservando memoria para el tablero!");
  }

  for(int i = 0; i < rows; i++) {
    miTablero->tablero[i] = (int*)malloc(columns * sizeof(int));
    if(miTablero->tablero[i] == NULL) {
      myError("Error reservando memoria para las columnas del tablero!");
    }
  }
  okay("Tablero inicializado con exito.");
}
```
Esta función primero reserva espacio para un vector de punteros(representan las columnas), que van a apuntar a lo que serían cada una de nuestras filas individuales.
Despues, para cada uno de los valores de las columnas, reserva el espacio necesitado para el vector de enteros (las filas)
Algo asi:
```
                            
    [r]                         
     │                          
     │                          
     │                          
   ┌─▼─┐      ┌───┬───┬───┬───┐ 
   │ 0 ├──────► 0 │ 1 │ 2 │ 3 │ 
   ├───┤  [c] └───┴───┴───┴───┘ 
   │ 1 │                        
   ├───┤                        
   │ 2 │                        
   ├───┤                        
   │ 3 │                        
   └───┘
```
De esta manera somos capaces de reservar solamente el espacio necesario para la matriz que vamos a usar.
Ademas de la funcion que reserva la memoria, tenemos que implementar la funcion que libera la memoria previamente reservada.
```c
void liberarTablero(tablero* miTablero) {
  //Liberamos memoria de las columnas de cada fila
  for(int i = 0; i < miTablero->rows; i++) {
    free(miTablero->tablero[i]);
  }
  //Liberamos la memoria del vector de punteros a cada fila
  free(miTablero->tablero);
}
```
**¿Porque lo hemos hecho asi?**
Lo hemos implementado así, porque de esta manera podemos acceder a la matriz de la misma manera que lo hariamos con una matriz estatica M[x][y].
El primer corchete indexara en el vector de punteros a vectores. Y el segundo indexara en el vector que representa esa fila.

## Implementaciones especiales
En un principio el tablero aparentemente, es 3x3 pero tal y como hemos decidido implementarlo, la matriz del tablero tiene tamaño 5x5 (N+2xM+2). Algo similar a este diagrama:
```
                           +--+--+--+--+--+
                           |  |  |  |  |  |
+--+--+--+                 +--------------+
|x |x |x |                 |  |x |x |x |  |
+--------+  Realmente es   +--------------+
|x |x |x |  +----------->  |  |x |x |x |  |
+--------+                 +--------------+
|x |x |x |                 |  |x |x |x |  |
+--+--+--+                 +--------------+
                           |  |  |  |  |  |
                           +--+--+--+--+--+
```
Queríamos hacer que tu desde la funcion que resuelve el tablero no te tuvieras que preocupar por las 2 filas y columnas extra y se tratara como una matrix NxM. Para ello en cada funcion de acceso a la matriz, ya sea para leer o para cambiar se le suma 1 al valor de coordenadas recibido.
```c
void colocarValor(tablero *miTablero, int row, int column, int value) {
  info("Colocando altura: %d en las coordenadas: %d, %d", value, row, column);
  //Mandar error si intentamos acceder a una direccion fuera de rango!
  if(miTablero->rows<= row+1 || miTablero->columns <= column + 1) {
    myError("Intentando acceder a una posicion no reservada en la funcion : %s", __FUNCTION__);
  }
  //Si la posicion es valida devolvemos su contenido
  miTablero->tablero[row+1][column+1] = value;
}
```
Ademas, antes de cada acceso a la matriz validamos que es correcto y si no es asi, llamamos a la macro, myError, que concatena un print con un mensaje de error y un traceback de llamadas con un exit.

Para evitar corrupciones de memoria hemos utilizado una herramienta que se llama valgrind que sirve para depurar el estado de la memoria para este tipo de casos.
La salida de este programa para un caso aleatorio es la siguiente:
```
==222670== Memcheck, a memory error detector
==222670== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==222670== Using Valgrind-3.20.0 and LibVEX; rerun with -h for copyright info
==222670== Command: ./colocar.out tests/test10.txt
==222670== Parent PID: 2404
==222670== 
==222670== 
==222670== HEAP SUMMARY:
==222670==     in use at exit: 0 bytes in 0 blocks
==222670==   total heap usage: 11 allocs, 11 frees, 83,629 bytes allocated
==222670== 
==222670== All heap blocks were freed -- no leaks are possible
==222670== 
==222670== For lists of detected and suppressed errors, rerun with: -s
==222670== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Como se puede observar de la salida, se hicieron 11 allocs, y 11 frees, lo que quiere decir que todo lo que en algun momento ha sido reservado, ha sido liberado entes de salir..

## Generador de tableros
Con las mismos funciones que hemos necesitado para resolver el tablero, es posible hacer una funcion que genere tableros para asi probar el programa.
De esta manera hemos podido escalar las mismas funciones para incluir otra feature!

## Optimizacion
Se tras un tiempo con el proyecto terminado, se nos ocurrio una optimizacion que reduciria bastante el coste en  tiempo de nuestro programa. La solucion consistiria en primero encontrar con backtracking, TODAS las soluciones de las filas, para posteriormente, hacer backtracking sobre las soluciones encontradas, hasta hallar una coincidiencia. Esto reduciria enormemente el coste en tiempo ya que reducimos el numero decasos evaluados.

Por cuestiones de tiempo no hemos podido implementarlp, pero nos ha parecido bien comentarlo aquí.

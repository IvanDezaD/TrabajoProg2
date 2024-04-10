# TrabajoProg2
Repositorio del trabajo de la asignatura programacion 2 del segundo semestre
## Objetivos principales
Nuestro objetivo principal es hacer un programa que sea capaz de resolver el siguiente problema:
- Siendo que se entrega un fichero con el siguiente formato: 
```
3 3
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
**¿Porque lo hemos hecho asi?**\n
Lo hemos implementado así, porque de esta manera podemos acceder a la matriz de la misma manera que lo hariamos con una matriz estatica M[x][y].
El primer corchete indexara en el vector de punteros a vectores. Y el segundo indexara en el vector que representa esa fila.

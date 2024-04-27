#pragma once
#include "colocar.h"
#include <iostream>

void guardarTablero(tablero *miTablero, std::string nombreArchivo){
    std::ofstream archivo;
    archivo.open(nombreArchivo);
    if(!archivo.is_open()){
        std::cout << "Error al abrir el archivo" << std::endl;
        return;
    }
    else{
        for(int i = 0; i < miTablero->rows; i++){
            for(int j = 0; j < miTablero->columns; j++){
                archivo << miTablero->tablero[i][j] << " ";
            }
            archivo << std::endl;
        }
    }
    archivo.close();
}
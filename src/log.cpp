#include "log.h"

using namespace std;

//Bloque de codigo que sirve para depurar mas comodamente ademas de mostrar errores.
#ifdef __DEBUG__
logLevel LOGLEVEL=WARNING; //Nivel de depuracion del programa

//Funcion que dado un nivel donde mostrar y un mensaje muestra ese mensaje dependiendo de la configuracion de depuracion y el nivel
//de depuracion recibido
void log(int logValue, string mensaje) {
  //En el caso de que lo que recibamos sea un error, siempre mostraremos por pantalla a no ser que  esta funcion no se haya definido al compilar
  if(logValue == ERROR){
    string prefix = "[\x1b[31mERROR\x1b[0m] ";
    string output = prefix + mensaje;
    cout << output << endl;
  }

  //Para el warning
  if(logValue == WARNING && (LOGLEVEL == INFO || LOGLEVEL == DEBUG || LOGLEVEL == WARNING)){
    string prefix = "[\x1b[33mWARNING\x1b[0m] ";
    string output = prefix + mensaje;
    cout << output << endl;
  }

  //Debug
  if(logValue == DEBUG && (LOGLEVEL == DEBUG || LOGLEVEL == INFO)){
    string prefix = "[\x1b[35mDEBUG\x1b[0m] ";
    string output = prefix + mensaje;
    cout << output << endl;
  }

  //En caso de recibir que sea info solo la mostraremos en el caso de que las opciones de depuracion sean 
  //las de informacion
  if(logValue == INFO && LOGLEVEL == INFO){
    string prefix = "[\x1b[36mINFO\x1b[0m] ";
    string output = prefix + mensaje;
    cout << output << endl;
  }

}
#endif

#ifndef __DEBUG__
logLevel LOGLEVEL = ERROR;
void log(int logValue, string mensaje) {
  if(logValue == ERROR){
    string prefix = "[\x1b[31mERROR\x1b[0m] ";
    string output = prefix + mensaje;
    cout << output << endl;
  }
}
#endif


int main(){
  LOG(INFO, "Esto es un mensaje de info");
  LOG(DEBUG, "Esto es un mensaje debug");
  LOG(WARNING, "Esto es un mensaje de warning");
  LOG(ERROR, "Esto es un mensaje de error");
}

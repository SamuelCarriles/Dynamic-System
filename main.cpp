#include <iostream>
#include <string>
#include <regex>
#include "SistemaDinamico.h"
#include <windows.h>
#include <mmsystem.h>
/* En este ejemplo la el objeto sistema crearía una matriz 3×3,
 pero más adelante, cuando se haga el menú principal del programa,
  el el orden/dimensión de la matriz podrá ser dicho por el usuario,
   introduciendo la cantidad de ecuaciones e incógnitas del sistema.*/
using namespace std;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    SistemaDinamico sistema(3,3);
    sistema.receptor_variables();
    sistema.receptor_ecuaciones();
    sistema.mostrar_matriz();
    return 0;
}
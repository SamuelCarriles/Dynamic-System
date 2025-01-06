#include <iostream>
#include <string>
#include <regex>
#include "SistemaDinamico.h"
#include <windows.h>
#include <mmsystem.h>

using namespace std;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    SistemaDinamico sistema(3,3);
    sistema.receptor_variables();
    sistema.receptor_ecuaciones();
    return 0;
}
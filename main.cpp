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
    return 0;
}
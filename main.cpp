#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>
#include "SistemaDinamico.h"
#include <windows.h>
#include <mmsystem.h>


using namespace std;

void resolver(){
    system("cls");
    cout<<"\n\n¿Cuántas variables utilizará?\n";
    int varCant;
    bool error=false;
    do {
        try {
            error=false;
            cout<<"\n\nCantidad de variables del sistema => ";
            cin>>varCant;
            if(cin.fail()||varCant<=0) throw 101;
            char c;
            if(cin.get(c)&&c=='.') throw 101;
        } catch(int x){
            error=true;
            varCant=0;
            cout<<"\n\nERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while(error);
    cout<<"\n\n¿Cuántas ecuaciones tendrá el sistema?\n";
    int ecuaCant=0;
    do {
        try {
            error=false;
            cout<<"\nCantidad de ecuaciones del sistema => ";
            cin>>ecuaCant;
            if(cin.fail()||ecuaCant<=0) throw 101;
            char c;
            if(cin.get(c)&&c=='.') throw 101;
        } catch(int x){
            error=true;
            ecuaCant=0;
            cout<<"\n\nERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while(error);
    system("cls");
    SistemaDinamico sistema(ecuaCant,varCant);
    sistema.receptor_variables();
    sistema.receptor_ecuaciones();
    sistema.mostrar_matriz();
    sistema.resolver_sistema();
}
void menu_principal(){
    system("cls");
    cout << "=========================================" << endl;
    cout << "        SYSTEM SOLVE - Menu Principal" << endl;
    cout << "=========================================" << endl;
    cout << "\n";
    cout << "1. Resolver un sistema de ecuaciones" << endl;
    cout << "2. Salir" << endl;
    int op=0;
    bool error;
    do{
        try{
            cout<<"\n\nEliges => ";
            cin>>op;
            if(cin.fail()||op==0) throw 101;
            char c;
            if(cin.get(c)&&c=='.') throw 101; 
            else {
                switch(op){
                    case 1:
                    resolver();
                    break;
                    case 2:
                    exit(0);
                    break;
                    default:
                    throw 101;
                }
            }
        } catch(int x){
            error=true;
            op=0;
            cout<<"\n\nERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while(error);
    
}
void opciones(){
    int op=0;
    bool error;
    cout<<"\n\n¿Qué desea hacer?\n1.Volver al menú principal\n2.Salir";
    do{
        try{
            cout<<"\n\nEliges => ";
            cin>>op;
            if(cin.fail()||op==0) throw 101;
            char c;
            if(cin.get(c)&&c=='.') throw 101; 
            else {
                switch(op){
                    case 1:
                    menu_principal();
                    break;
                    case 2:
                    exit(0);
                    break;
                    default:
                    throw 101;
                }
            }
        } catch(int x){
            error=true;
            op=0;
            cout<<"\n\nERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while(error);
}
int main(){
    SetConsoleOutputCP(CP_UTF8);
    menu_principal();
    opciones();
    return 0;
}
#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <mmsystem.h>
#include "SistemaDinamico.h"
using namespace std;

SistemaDinamico::SistemaDinamico(int num_ecuaciones, int num_icognitas) 
: cant_ecuaciones(num_ecuaciones), cant_icognitas(num_icognitas), dimension_matriz_ampliada(num_icognitas+1)
{
    matriz_ampliada=new double*[cant_ecuaciones];
    matriz_equivalente=new double*[cant_ecuaciones];
    for(int i=0;i<cant_ecuaciones;i++){
        matriz_ampliada[i]=new double[dimension_matriz_ampliada];
        matriz_equivalente[i]=new double[dimension_matriz_ampliada];
    }
    variables=new char[cant_icognitas];
} // Constructor Completado!!

void SistemaDinamico::crear_matriz(double* fila,int index,string matriz){
    if(matriz=="matriz-ampliada"){
        for(int i=0;i<dimension_matriz_ampliada;i++){
            matriz_ampliada[index][i]=fila[i];
        }
    } else if(matriz=="matriz-equivalente"){
        for(int i=0;i<dimension_matriz_ampliada;i++){
            matriz_ampliada[index][i]=fila[i];
        } 
    } else cout<<"\nERROR_202!\n";
} // M.Priv Completado!! 
// Recibe el arreglo de la fila, la fila que es y a qué matriz pertenece.
double* SistemaDinamico::extraer_coeficientes(string* cadena){
    //falta escribir este método
}


void SistemaDinamico::receptor_variables() {
    char* var=new char[cant_icognitas];
    for(int i=0;i<cant_icognitas;i++){
        var[i]='\0';
    }
    bool error;
    cout<<"\nIntroduzca las variables que se utilizarán: \n";
    for(int i=0;i<cant_icognitas;i++){
        do {
            error=false;
            cout<<"\nVariable "<<i+1<<" => ";
            cin>>var[i];
            cin.clear();
            cin.ignore(1000, '\n');
            if(cin.fail()||!((var[i]>='a'&&var[i]<='z')||(var[i]>='A'&&var[i]<='Z'))){
                cout<<"\nERROR_101! Variable no válida. Vuelva a intentarlo . . .\n";
                var[i]='\0';
                error=true;
            } else if(i>0&&var[i]==var[i-1]){
                    cout<<"\nERROR_102! Variable repetida. Vuelva a intentarlo . . .\n";
                    var[i]='\0';
                    error=true;
            }
        } while (error==true);
    }
    do {
        error=false;
        cout<<"\n¿Desea utilizar estas variables? [";
        for(int i=0;i<cant_icognitas;i++){
            cout<<var[i]<<" ";
        }
        cout<<"] (s/n)\n=> ";
        char sn;
        cin>>sn;
        cin.ignore(1000,'\n');
        if(cin.fail()||(!(sn=='s'||sn=='S'||sn=='n'||sn=='N'))){
            cout<<"\nERROR_101! Respuesta no válida. Vuelva a intentarlo . . .";
            sn='\0';
            error=true;
        } else if(sn=='S'||sn=='s'){
            cout<<"\n¡Perfecto! Presione ENTER para continuar . . .";
            cin.get();
            system("cls");
        } else if(sn=='n'||sn=='N'){
            cout<<"\nVale. Intente otra vez, por favor . . .\n";
            receptor_variables();
        }
    } while (error==true);
    for(int i=0;i<cant_icognitas;i++){
        variables[i]=var[i];
    }
    delete[] var;

} // M.Pub Completado!!
void SistemaDinamico::receptor_ecuaciones() {
    bool error;
    string* cadena=new string[cant_ecuaciones];
    cout<<"\nIngrese las "<<cant_ecuaciones<<" ecuaciones del sistema: \n";
    cout<<"\n(Recuerde que debe usar las variables: ";
    for(int i=0;i<cant_icognitas;i++){
        cout<<variables[i]<<" ";
    }
    cout<<")"<<endl;
    for(int i=0;i<cant_ecuaciones;i++){
        do {
            error=false;
            cout<<"\nEcuación "<<i+1<<" => ";
            getline(cin,cadena[i]);
            if(cin.fail()){
                cout<<"\nERROR_201! Ecuación no válida. Vuelva a intentarlo . . .\n";
                error=true;
                cin.clear();
                cadena[i]="";
            }
        } while(error==true);
    }
    for(int i=0;i<cant_ecuaciones;i++){
        crear_matriz(extraer_coeficientes(cadena[i]),i,"matriz-amplidada");
        crear_matriz(extraer_coeficientes(cadena[i]),i,"matriz-equivalente");
        cout<<"\nEcuación "<<i+1<<" => "<<cadena[i]<<endl;
    }
    cout<<"\n¡Perfecto! Presione ENTER para continuar . . .";
    cin.get();

} // M.Pub Completado!!


SistemaDinamico::~SistemaDinamico() {
    delete[] matriz_equivalente;
    delete[] matriz_ampliada;
    delete[] variables;
} // Destructor Completado!!
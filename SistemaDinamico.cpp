#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>
#include <windows.h>
#include <mmsystem.h>
#include "SistemaDinamico.h"
using namespace std;

SistemaDinamico::SistemaDinamico(int num_ecuaciones, int num_incognitas) 
: cant_ecuaciones(num_ecuaciones), cant_incognitas(num_incognitas), dimension_matriz_ampliada(num_incognitas+1)
{
    matriz_ampliada=new double*[cant_ecuaciones];
    matriz_equivalente=new double*[cant_ecuaciones];
    for(int i=0;i<cant_ecuaciones;i++){
        matriz_ampliada[i]=new double[dimension_matriz_ampliada];
        matriz_equivalente[i]=new double[dimension_matriz_ampliada];
    }
    for(int i=0;i<cant_ecuaciones;++i){
        for(int j=0;j<dimension_matriz_ampliada;++j){
            matriz_equivalente[i][j]=0;
            matriz_ampliada[i][j]=0;
        }
    }
    variables=new char[cant_incognitas];
    for(int i=0;i<cant_incognitas;++i) variables[i]='\0';
} // Constructor Completado!!


 // Métodos privados
 
double SistemaDinamico::de_string_a_numero(string numString) {
    double numerador=0;
    double denominador=0;
    bool fraccion=false;
    string num,den;
    try{if(numString.empty()) throw 203;} catch(int x){cout<<"\nERROR_"<<x<<"!"; }
    for(const auto& c : numString){
        if(c=='/'){
            fraccion=true;
            continue;
        }
        if(fraccion==false){
            num+=c;
            continue;
        } else {
            den+=c;
            continue;
        }
    }
    if(fraccion==true){
    numerador=stod(num);
    denominador=stod(den);
    return numerador/denominador;
    }
    numerador = stod(num);
    return numerador;
} // M.Priv Completado!!
void SistemaDinamico::crear_matriz(double* fila,int index,string matriz){
    if(matriz=="matriz-ampliada"){
        for(int i=0;i<dimension_matriz_ampliada;i++){
            matriz_ampliada[index][i]=fila[i];
        }
    } else if(matriz=="matriz-equivalente"){
        for(int i=0;i<dimension_matriz_ampliada;i++){
            matriz_equivalente[index][i]=fila[i];
        } 
    }
} // M.Priv Completado!! 
double* SistemaDinamico::extraer_coeficientes(string& cadena){
    double* filaCoeficientes=new double[dimension_matriz_ampliada];
    for(int i=0;i<dimension_matriz_ampliada;++i) {
        filaCoeficientes[i]=0;
    }
    string ecuacionRe;
    for(const auto& c : cadena){
        if(c!=' ') ecuacionRe+=c;
    }
    string variablesPatron="(";
    for(int i=0;i<cant_incognitas;i++){
        variablesPatron+=variables[i];
        if(i<cant_incognitas-1){
            variablesPatron+="|";
        }
    }
    variablesPatron+=")";
    string coefPat=R"((\+|-)?\(?(-?\d*(\.\d+)?(\/(-?\d+(\.\d+)?))?)\)?)"+variablesPatron+R"((\/(-?\d+(\.\d+)?))?\)?)";   
    /*Info sobre el contenido de cada grupo del patrón-> (\+|-)?\(?(-?\d*(\.\d+)?(\/(-?\d+(\.\d+)?))?)\)?(x|y|z)(\/(-?\d+(\.\d+)?))?\)?

        grupo 1: Operación que relaciona este término con el anterior (si no está vacío significa que es el primer término, aunque este término primero puede ser negativo).
       *grupo 2: Coeficiente completo que está antes de la variable (no importa si es una fracción)
        grupo 3: Parte decimal del coeficiente (en caso de que sea una fracción sería la parte decimal del numerador. Se vería así; ".98")
        grupo 4: Denominador del coeficiente con '/' incluido(si existe se ve así: "/8.3")
        grupo 5: Denominador del coeficiente real, es decir, el que de verdad se va a usar para calcular
        grupo 6: Parte decimal del denominador (ej: ".967")
        grupo 7: Variable correspondiente (ej: 'y')
        grupo 8: Denominador con '/' incluido (en caso de que el término tenga la forma "5y/2". Se vería así: "/2")
        grupo 9: Denominador real (es decir, sin el '/')
        grupo 10: Parte decimal de ese denominador
    */
    regex patron(coefPat);
    regex terminoInd(R"(=(\+|-)?\(?(-?\d*(\.\d+)?(\/(-?\d+(\.\d+)?))?)\)?$)");
    //Los grupos importantes de este patrón son: grupo 1 -> signo antes del paréntesis o del término.  grupo 2 -> término completo
    auto inicio = sregex_iterator(ecuacionRe.begin(), ecuacionRe.end(), patron);
    auto fin = sregex_iterator();
    for(auto i=inicio;i!=fin;++i){
        smatch match = *i;
        double coeficiente=0;
        int valor=1;
        if(match[1].str()=="+"||match[1].str().empty()) valor=1;
        else if(match[1].str()=="-") valor=-1;
        if(match[2].str().empty()&&match[9].str().empty()) coeficiente=valor*1;
        else if(match[2].str().empty()&&!match[9].str().empty()) coeficiente = valor*(1/de_string_a_numero(match[9].str()));
        else if(!match[2].str().empty()&&match[9].str().empty()) coeficiente = valor*de_string_a_numero(match[2].str());
        else if(!match[2].str().empty()&&!match[9].str().empty()) coeficiente = valor*(de_string_a_numero(match[2].str())/de_string_a_numero(match[9].str()));
        for(int j=0;j<cant_incognitas;++j) {
            if(variables[j]==match[7].str()[0]) filaCoeficientes[j]+=coeficiente;
        }
    }
    inicio = sregex_iterator(ecuacionRe.begin(), ecuacionRe.end(), terminoInd);
    for(auto i = inicio;i!=fin;++i){
        smatch match = *i;
        int valor=1;
        if(match[1].str()=="+"||match[1].str().empty()) valor=1;
        else if(match[1].str()=="-") valor=-1;
        filaCoeficientes[cant_incognitas]=valor*de_string_a_numero(match[2].str());
    }
    return filaCoeficientes;
} // M.Priv Completado!!
string SistemaDinamico::patron_validacion(){
    string variablesPatron="(";
    for(int i=0;i<cant_incognitas;i++){
        variablesPatron+=variables[i];
        if(i<cant_incognitas-1){
            variablesPatron+="|";
        }
    }
    variablesPatron+=")";
    string validacionPatron=R"(^\s*((-?\s*\()?\s*(-?\s*\d*(\.\d+)?(\s*/\s*-?\s*\d+(\.\d+)?)?)\s*\)?\s*)"+variablesPatron+R"((\s*/\s*-?\s*\d+(\.\d+)?)?\s*\)?)(\s*(\+|-)(\s*\(\s*-?)?(\s*\d*(\.\d+)?(\s*/\s*-?\s*\d+(\.\d+)?)?)\s*\)?\s*)"+variablesPatron+R"((\s*/\s*-?\s*\d+(\.\d+)?)?\s*\)?\s*)*\s*=\s*(-?\s*\()?\s*(-?\s*\d+(\.\d+)?(\s*/\s*-?\s*\d+(\.\d+)?)?)\)?\s*$)";
    return validacionPatron;
} // M.Priv Completado!!
bool SistemaDinamico::validador_de_ecuaciones(const string& ecuacion){
    // Añadir un comprobador para saber si hay cantidad igual de paréntesis de abrir y cerrar, porque es error.
    int parentAbierto=0,parentCerrado=0;
    for(const auto& i : ecuacion){
        if(i=='(') parentAbierto++;
        else if(i==')') parentCerrado++;
    }
    regex patron(patron_validacion());
    if(regex_match(ecuacion,patron)&&parentAbierto==parentCerrado){
        return true;
    }
    return false;
} // M.Priv Completado!!
void SistemaDinamico::clasificar_matriz(){
    int rango1=0,rango2=0,contador=0;
    for(int i=0;i<cant_ecuaciones;++i){
        if(matriz_equivalente[i][cant_incognitas]!=0) rango1++;
        for(int j=0;j<cant_incognitas;++j){
            if(matriz_equivalente[i][j]!=0) contador++;
        }
        if(contador>0) rango2++;
        contador=0;
    }
    if(((rango1==rango2)&&(cant_incognitas==cant_ecuaciones))||((rango1==rango2)&&(cant_incognitas<cant_ecuaciones))) {
        cout<<"\n\nLa matriz es compatible determinada.\n";
        cout<<"\n\nPresione ENTER para continuar . . .";
        cin.ignore(1000,'\n');
    }
    else if((rango1==rango2)&&(cant_incognitas>cant_ecuaciones)) {
        cout<<"\n\nLa matriz es compatible indeterminada.\n";
        cout<<"\n\nPresione ENTER para continuar . . .";
        cin.ignore(1000,'\n');
    }
    else if(rango1<rango2){
        cout<<"\nLa matriz es incompatible, por lo tanto, el sistema no tiene solución.\n\n";
        cout<<"\n\nPresione ENTER para continuar . . .";
        cin.ignore(1000,'\n');
    }
    else cout<<"\n\nERROR!";
}
void SistemaDinamico::escalonar(){
    bool sig=false;
    double factores[2]={0,0};
    cout<<"\n\nTransformaciones realizadas: ";

    int filaMayorPivote=0;
    for(int i=1;i<cant_ecuaciones;++i){
        if(abs(matriz_equivalente[i][0])>abs(matriz_equivalente[i-1][0])) filaMayorPivote=i;
        else filaMayorPivote=i-1;
    }
    if(filaMayorPivote!=0&&(matriz_equivalente[0][0]!=matriz_equivalente[filaMayorPivote][0])){
        swap(matriz_equivalente[0],matriz_equivalente[filaMayorPivote]);
    cout<<"\nSe intercambió la fila "<<filaMayorPivote+1<<" por la fila 1 buscando el pivote de mayor módulo...\n";
    mostrar_matriz();
    }

    for(int i=0;i<cant_incognitas;++i){
        if(matriz_equivalente[i][i]==0){
            for(int k=i+1;k<cant_ecuaciones;++k){
                if((k==cant_ecuaciones-1)&&matriz_equivalente[k][i]==0) sig=true;
                else if(matriz_equivalente[k][i]==0) continue;
                else if(matriz_equivalente[k][i]!=0){
                    swap(matriz_equivalente[i],matriz_equivalente[k]);
                    cout<<"\n\nFila "<<i+1<<" <--> "<<k+1<<" Fila.\n";
                    mostrar_matriz();
                    break;
                }
            }
        }
        factores[0]=matriz_equivalente[i][i];
        if(sig) {
            i++;
            factores[0]=matriz_equivalente[i-1][i];
        }
        for(int j=i+1;j<cant_ecuaciones;++j){
            if(sig) {
                j--;
                sig=false;
            }

            if(matriz_equivalente[j][i]==0) continue;
            else {
                factores[1]=matriz_equivalente[j][i];
                for(int h=0;h<dimension_matriz_ampliada;++h){
                    matriz_equivalente[j][h]=(factores[1]*matriz_equivalente[i][h])-(factores[0]*matriz_equivalente[j][h]);
                }
                cout<<"\n\n("<<factores[1]<<"*Fila "<<i+1<<") - ("<<factores[0]<<"*Fila "<<j+1<<")\n\n";
                mostrar_matriz();
            }

        }
    }
    cout << "\n¡Proceso de escalonamiento completado!\n";
}
/*void SistemaDinamico::solucion_determinada(){
    double factores[2]={0,0};
    for(int i=cant_incognitas-1;i>0;--i){
        factores[0]=matriz_equivalente[i][i];
        for(int j=cant_incognitas-1;i>0;--i){

        }
    }
}*/
 // Métodos públicos

void SistemaDinamico::receptor_variables() {
    char* var=new char[cant_incognitas];
    for(int i=0;i<cant_incognitas;i++){
        var[i]='\0';
    }
    bool error;
    cout<<"\nIntroduzca las variables que se utilizarán: \n";
    for(int i=0;i<cant_incognitas;i++){
        do {
            try {
                error=false;
                cout<<"\nVariable "<<i+1<<" => ";
                cin>>var[i];
                cin.ignore(1000, '\n');
                if(cin.fail()||!((var[i]>='a'&&var[i]<='z')||(var[i]>='A'&&var[i]<='Z'))){
                    throw 101; 
                } else if(i>0){
                    for(int j=0;j<i;j++){
                        if(var[i]==var[j]){
                            throw 102;
                            break;
                        }
                    }
                }
            } catch(int x){
                var[i]='\0';
                error=true;
                cout<<"ERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
                cin.clear();
                cin.ignore(1000,'\n');
            }
        } while (error==true);
    }
    do {
        char sn;
        try {
            error=false;
            cout<<"\n¿Desea utilizar estas variables? [";
            for(int i=0;i<cant_incognitas;i++){
                if(i!=(cant_incognitas-1))cout<<var[i]<<" ";
                else cout<<var[i];
            }
            cout<<"] (s/n)\n=> ";
            cin>>sn;
            cin.ignore(1000,'\n');
            if(cin.fail()||(!(sn=='s'||sn=='S'||sn=='n'||sn=='N'))){
                throw 101;
            } else if(sn=='S'||sn=='s'){
                cout<<"\n¡Perfecto! Presione ENTER para continuar . . .";
                cin.get();
                system("cls");
            } else if(sn=='n'||sn=='N'){
                cout<<"\nVale. Intente otra vez, por favor . . .\n";
                receptor_variables();
            }
        } catch(int x){
            sn='\0';
            error=true;
            cout<<"ERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
            cin.clear();
            cin.ignore(1000,'\n');
        }
    } while (error==true);
    for(int i=0;i<cant_incognitas;i++){
        variables[i]=var[i];
    }
    delete[] var;

} // M.Pub Completado!!
void SistemaDinamico::receptor_ecuaciones() {
    bool error;
    string* cadena=new string[cant_ecuaciones];
    cout<<"\nIngrese las "<<cant_ecuaciones<<" ecuaciones del sistema. \nTenga en cuenta que deben tener la forma \"<variables> = <término independiente>\",\n es decir, debe ser una ecuación reducida con un solo término independiente. Por ejemplo: \"-(3/4)x+(5y/0.25)+(-2z)=12.34/-4.08\"\n";
    cout<<"\n(Recuerde que debe usar las variables: ";
    for(int i=0;i<cant_incognitas;i++){
        if(i<(cant_incognitas-1))cout<<variables[i]<<" ";
        else if(i==(cant_incognitas-1)) cout<<variables[i];
    }
    cout<<")"<<endl;
    for(int i=0;i<cant_ecuaciones;i++){
        do {
            try {
                error=false;
                cout<<"\nEcuación "<<i+1<<" => ";
                getline(cin,cadena[i]);
                if(cin.fail()){
                    throw 202;
                }
                error=validador_de_ecuaciones(cadena[i])==false? true:false;
                if(error==true) throw 201;
            } catch(int x){
                error=true;
                cadena[i]="";
                cout<<"ERROR_"<<x<<"!\n Presione ENTER para volver a intentarlo . . .";
                cin.clear();
                cin.ignore(100,'\n');
            }
        } while(error==true);
    }
    for(int i=0;i<cant_ecuaciones;i++){
        crear_matriz(extraer_coeficientes(cadena[i]),i,"matriz-amplidada");
        crear_matriz(extraer_coeficientes(cadena[i]),i,"matriz-equivalente");
    }
    delete[] cadena;
    cout<<"\n¡Perfecto! Presione ENTER para continuar . . .";
    cin.get();

} // M.Pub Completado!!
void SistemaDinamico::mostrar_matriz() {
    cout<<"\n\nMatriz actual: \n\n";
    for(int i=0;i<cant_ecuaciones;++i){
        for(int j=0;j<dimension_matriz_ampliada;++j){
            if(j==cant_incognitas) cout<<setw(9)<<"|"<<setw(10)<<matriz_equivalente[i][j];
            else cout<<setw(20)<<matriz_equivalente[i][j];
        }
        cout<<endl<<endl;
    }
    cout<<"\n\nPresione ENTER para continuar . . .";
    cin.ignore(1000,'\n');
} // M.Pub Completado!!
void SistemaDinamico::resolver_sistema(){
    escalonar();
    clasificar_matriz();
}


SistemaDinamico::~SistemaDinamico() {
    delete[] matriz_equivalente;
    delete[] matriz_ampliada;
    delete[] variables;
} // Destructor Completado!!
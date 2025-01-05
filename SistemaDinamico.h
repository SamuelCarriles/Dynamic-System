#ifndef SISTEMADINAMICO_H
#define SISTEMADINAMICO_H

#include <string>

using namespace std;
class SistemaDinamico 
{
    private:
    double** matriz_ampliada;
    double** matriz_equivalente;
    char* variables;
    int cant_ecuaciones,cant_icognitas,dimension_matriz_ampliada;
    
    // Métodos privados
    void crear_matriz(double* fila,int index,string matriz);
    double* extraer_coeficientes(string* cadena);
    bool validador_de_ecuaciones(const string& cadena);
    string patron_validacion();

    public:
    SistemaDinamico(int num_ecuaciones, int num_icognitas);
    
    // Métodos públicos
    void receptor_variables();
    void receptor_ecuaciones();
    void resolver_sistema();
    void mostrar_matriz();

    ~SistemaDinamico();
};

#endif
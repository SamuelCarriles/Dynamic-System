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
    int cant_ecuaciones,cant_incognitas,dimension_matriz_ampliada;
    
    // Métodos privados
    double de_string_a_numero(string numString);
    void crear_matriz(double* fila,int index,string matriz);
    double* extraer_coeficientes(string& cadena);
    bool validador_de_ecuaciones(const string& ecuacion);
    string patron_validacion();
    void clasificar_matriz();
    void escalonar();
    void solucion_determinada();
    void solucion_indeterminada();

    public:
    SistemaDinamico(int num_ecuaciones, int num_incognitas);
    
    // Métodos públicos
    void receptor_variables();
    void receptor_ecuaciones();
    void resolver_sistema();
    void mostrar_matriz();

    ~SistemaDinamico();
};
 
#endif
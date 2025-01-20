# Dynamic-System
Programa desarrollado para el proyecto final de la asignatura *Introducción a la Programación I* en la *Universidad de las Ciencias Informáticas*.
## Descripción del proyecto
Se busca desarrollar un programa que, en síntesis, haga lo siguiente:
- Pida al usuario un sistema de ecuaciones.
- Cree una matriz con los coeficientes encontrados dentro de cada ecuación.
- Escalone la matriz por el método de Gauss para saber si el sistema tiene solución o no.
- Resolver el sistema y mostrar el resultado al usuario.

**Importante:** Todo esto debe hacerse usando arreglos y punteros, pues es el objetivo que se evaluará.
## Plan de acción
- [x] Implementar un método que utilice la librería **regex** para validar las ecuaciones, hallar cada coeficiente y cada variable y llevarlos a arreglos separados.
- [x] Implementar un método que facilite la creación de dos matrices: la ampliada y la equivalente. La ampliada para guardar los coeficientes y términos independientes originales, y la equivalente para aplicarle los procedimientos necesarios para la resolución del sistema.
- [x] Implementar un método para escalonar matrices e identificar su compatibilidad o no.
- [x] Implementar un método para hallar el conjunto solución del sistema si es determinado.
- [x] Crear el menú principal del programa.
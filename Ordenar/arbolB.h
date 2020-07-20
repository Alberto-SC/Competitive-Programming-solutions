#include <stdio.h>
#include <stdlib.h>

//Declaracion de la estructura tRegistro que tendrá



//Estructura Arbol que toma la estructura de un Nodo
typedef struct Arbol
{
int Dato;
struct Arbol* izq;
struct Arbol* der;
}Arbol;

typedef Arbol* ARBOL;
//declaración de metodos
ARBOL crear();
ARBOL crearArbol();
void insertar(ARBOL *,int);
void preOrden(ARBOL A);
void postOrden(ARBOL A);
void inOrden(ARBOL A);
int buscar (ARBOL A, int elem);
void reemplazar(ARBOL,ARBOL);
int numElementos(ARBOL,int);
int AlturaArbol(ARBOL,int);
int auxAltura(ARBOL,int,int);
void borrar(ARBOL,int elem);

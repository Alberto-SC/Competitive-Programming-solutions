//*****************************************************************
//M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ
//Curso: Análisis de algoritmos
//(C) Enero 2013
//ESCOM-IPN
//Ejemplo de medición de tiempo en C y recepción de parametros en C bajo UNIX
//Compilación: "gcc main.c tiempo.x  -o main(teimpo.c si se tiene la implementación de la libreria o tiempo.o si solo se tiene el codigo objeto)"
//Ejecución: "./main n" (Linux y MAC OS)
//*****************************************************************
//*****************************************************************
//LIBRERIAS INCLUIDAS
//*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//********************************************************************************
//DECLARACION DE ESTRUCTURAS
//********************************************************************************
typedef struct Arbol
{
int Dato;
struct Arbol* izq;
struct Arbol* der;
}Arbol;

typedef struct Nodo_Pila{
	struct Arbol* AR;
	struct Nodo_Pila* anterior;
}Nodo_Pila;

typedef struct{
	Nodo_Pila* tope;
}Pila;


typedef Pila* PILA;
typedef Arbol* ARBOL;
//*****************************************************************
//DECLARACIÓN DE FUNCIONES
//*****************************************************************
void insertar(ARBOL * ,int);
void inOrden(ARBOL,int[]);
void OrdenaConArbolBinario(int *,int);
PILA crearPila();
ARBOL pop(PILA);
void push(PILA,ARBOL);
int Empty(PILA );

//*****************************************************************
//PROGRAMA PRINCIPAL
//*****************************************************************
int main (int argc, char* argv[])
{
	//******************************************************************
	//Variables del main
	//******************************************************************
	double utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
	int n; 	//n determina el tamaño del algorito dado por argumento al ejecutar
	int i; //Variables para loops
	int b; //Numero para buscar
	int j = 0,m;
	//Si no se introducen exactamente 2 argumentos (Cadena de ejecución y cadena=n)
	if (argc!=2)
	{
		printf("\nIndique el tamanio del algoritmo - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	}
	//Tomar el segundo argumento como tamaño del algoritmo
	else
	{
		n=atoi(argv[2]);
	}

	//******************************************************************
	//Iniciar el conteo del tiempo para las evaluaciones de rendimiento
	//******************************************************************
	uswtime(&utime0, &stime0, &wtime0);
	//******************************************************************

	//******************************************************************
	//Algoritmo
	//******************************************************************
	b = atoi(argv[1]);
	m = strtol(argv[2],NULL,10);
	int *A;
	A = (int*)malloc(sizeof(int)*m);
	for(j = 0; j<m;j++){
		scanf("%d",&A[j]);
	}
	OrdenaConArbolBinario(A,m,b);
	for(i=0;i<n;i++)
		for(i=0;i<n;i++)
			n=n;
	free(a);							//Liberacion de memoria
	//******************************************************************

	//******************************************************************
	//Evaluar los tiempos de ejecución
	//******************************************************************
	uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");

	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	//******************************************************************

	//Terminar programa normalmente
	exit (0);
}

//************************************************************************
//DEFINICIÓN DE FUNCIONES
//************************************************************************

int Buscar(ARBOL abb,int b){
    int i = 0;
    ARBOL aux = abb;
    do{
        if(b< aux->Dato){
            aux = aux->izq;
        }else if(b> aux->Dato{
            aux = aux->der;
        }else return 1;
    }while(aux != NULL);
}



void insertar(ARBOL *A, int e){
	int f = -1;
   if (*A == NULL){
   			*A = (ARBOL)malloc(sizeof(Arbol));
   		if(*A != NULL){
		    (*A)->Dato = e;
			(*A)->der=NULL;
			(*A)->izq=NULL;
	   }
	}
	else{
	while(f == -1){
		if(e<(*A)->Dato){
			if((*A)->izq!= NULL){
				A = &((*A)->izq);
			}else{
				(*A)->izq = (ARBOL)malloc(sizeof(Arbol));
				(*A)->izq->Dato = e;
				(*A)->izq->der=NULL;
				(*A)->izq->izq=NULL;
				f = 0;
			}
		}else if(e>(*A)->Dato){
			if((*A)->der!=NULL){
				A = &((*A)->der);
			}
			else{
				(*A)->der = (ARBOL)malloc(sizeof(Arbol));
				(*A)->der->Dato = e;
				(*A)->der->der=NULL;
				(*A)->der->izq=NULL;
				f= 0;

			}
		}

	}
}
}

void BusquedaConArbolBinario(int *A,int n,int b){
	int i;
	ARBOL abb;
	abb = NULL;
	for(i = 0;i<n;i++){
		insertar(&abb,A[i]);
	}
	if(Buscar(abb,b)==1)
		printf("Elemento encontrado");
	else
		printf("El elemento no se encuentra en la lista")
	for(i = 0;i<n;i++){
		printf("%d\n",A[i]);
	}
}
PILA crearPila(){
	PILA S;
	S=(PILA)malloc(sizeof(Pila));
	S->tope=NULL;
	return S;
}
void push(PILA S,ARBOL A){
	Nodo_Pila* np;
	np=(Nodo_Pila*)malloc(sizeof(Nodo_Pila));
	np->AR = A;
	np->anterior=S->tope;
	S->tope=np;

}

ARBOL pop(PILA S){
	ARBOL A;
	Nodo_Pila* np;
	A=S->tope->AR;
	np=S->tope->anterior;
	free(S->tope);
	S->tope=np;
	return A;
}
int Empty(PILA S){
	if(S->tope==NULL)
	  return 1;
	return 0;
}

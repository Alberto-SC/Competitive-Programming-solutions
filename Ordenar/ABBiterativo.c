#include <stdlib.h>
#include <stdio.h>



//___________________________________________________//
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
//____________________________________________________//



void insertar(ARBOL * ,int);
void inOrden(ARBOL,int[]);
void OrdenaConArbolBinario(int *,int);
PILA crearPila();
ARBOL pop(PILA);
void push(PILA,ARBOL);
int Empty(PILA );


//____________________________________________________//


int main(int argc, char *argv[]){
	int i = 0,n;
	n = strtol(argv[1],NULL,10);
	int *A;
	A = (int*)malloc(sizeof(int)*n);
	for(i = 0; i<n;i++	){
		scanf("%d",&A[i]);
	}
	OrdenaConArbolBinario(A,n);
	return 0;
}

void inOrden(ARBOL abb,int *A){
    PILA p;
    int i = 0;
    p = crearPila();
    ARBOL aux = abb;
    do{
        if(aux != NULL){
            push(p,aux);
            aux = aux->izq;
        }else if(Empty(p)==0){
            aux = pop(p); 
            A[i] = aux->Dato;
            i++;
            aux = aux->der;	
        }
    }while(Empty(p)==0 || aux != NULL);
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

void OrdenaConArbolBinario(int *A,int n){
	int i;
	ARBOL abb;
	abb = NULL;	
	for(i = 0;i<n;i++){
		insertar(&abb,A[i]);
	}
	inOrden(abb,A);
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



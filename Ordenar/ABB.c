#include <stdlib.h>
#include <stdio.h>
typedef struct Arbol
{
int Dato;
struct Arbol* izq;
struct Arbol* der;
}Arbol;
typedef Arbol* ARBOL;

void insertar(ARBOL * ,int);
void inOrden(ARBOL,int[]);
void OrdenaConArbolBinario(int [],int);
ARBOL newNodo();

int main(int argc, char *argv[]){
	int i = 0,n;
	n = strtol(argv[1],NULL,10);
	char a[20];
	int A[n];
	FILE *arch;
    arch = fopen("numeros10millones.txt", "r");
    if (arch == NULL) 
		printf("Error opening file");
   else {
    while(fgets(a, 20, (FILE*) arch)&& i<=n) {
        A[i] = strtol(a,NULL,10);
        i++;
    }
}
	fclose(arch);
	OrdenaConArbolBinario(A,n);
	return 0;
}

void inOrden(ARBOL abb,int A[]){
    if(abb != NULL)
    {		
        inOrden(abb->izq,A);

        printf("\n%d \n ", abb->Dato);
        inOrden(abb->der,A);
    }
}		
	
void insertar(ARBOL *A, int e){
   if (*A == NULL){
   		*A = (ARBOL)malloc(sizeof(Arbol));
   		if(*A != NULL){
		    (*A)->Dato = e;
			(*A)->der=NULL;
			(*A)->izq=NULL;
	       
	   }
	}
 	else {
 		if(e> (*A)->Dato){
    		insertar(&((*A)->der), e);
    	}
  		else if(e< (*A)->Dato){
			insertar(&((*A)->izq), e);
		}
	}
}

void OrdenaConArbolBinario(int A[],int n){
	int i;
	ARBOL abb;
	abb = NULL;	
	for(i = 0;i<n;i++){
		printf("  %d\n",A[i]);
		insertar(&abb,A);
	}
	inOrden(abb,A);
}

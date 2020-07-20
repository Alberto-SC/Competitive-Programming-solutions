
#include "arbolB.h"

ARBOL crear(){
	ARBOL A;
	A = NULL;
	return A;

}
ARBOL crearArbol(int e){
	ARBOL A;
	A= (ARBOL)malloc(sizeof(ARBOL));
	A->Dato = e;
	A->der=NULL;
	A->izq=NULL;

	return A;
}


int AlturaArbol(ARBOL a, int altura) {
   
   altura = auxAltura(a, 0, altura);
   return altura;
}

int auxAltura(ARBOL nodo, int a, int altura) {
   
   if(nodo->izq) 
	altura=auxAltura(nodo->izq, a+1, altura); 
   if(nodo->der)  
	 altura=auxAltura(nodo->der, a+1, altura);  
   if(nodo->izq == NULL && nodo->der == NULL  && a > altura)
	 altura = a;
	return altura; 
}




int numElementos(ARBOL A,int i){	
	if(A != NULL)
    {
        i++;
	i = numElementos(A->izq,i);
	i = numElementos(A->der,i);
	
    }	
	return i;
	

}
void insertar(ARBOL * A, int elem)
{
   if (*A == NULL)
  {
    *A = crearArbol(elem);
 
}
	//CONDICION PARA ALMACENAR EN EL NODO DERECHO O IZQUIERDO
 else if(elem%2 != 0){ 
    	insertar(&(*A)->der, elem);
    	}
  else if (elem%2 == 0){
	insertar(&(*A)->izq, elem);

}
}

void preOrden(ARBOL A){
    if(A!= NULL)
    {
        printf("Los datos del arbol en preOrden son: %d\n", A->Dato);
        preOrden(A->izq);
        preOrden(A->der);
    }	
}

void postOrden(ARBOL A){
    if(A!= NULL)
    {
        postOrden(A->izq);
        postOrden(A->der);
        printf("%d -  ", A->Dato);
    }
}

void inOrden(ARBOL A){
    if(A!= NULL)
    {
        inOrden(A->izq);
        printf("%d  -  ", A->Dato);
        inOrden(A->der);
    }
}

 int buscar(ARBOL A, int elem)
{
  if(A!= NULL)
    {
	if(A->Dato == elem)
		return 1;
        buscar(A->izq,elem);
        buscar(A->der,elem);
    }

}


void borrar(ARBOL A, int elem)

{


  if(A != NULL)
    {
	if(A->Dato == elem && A->izq == NULL && A->der == NULL)
		{
    free(A);
    
  }
  
	
        borrar(A->izq,elem);
        borrar(A->der,elem);
    }

}

/*void reemplazar(ARBOL A, ARBOL aux)
{
  if (A->der == NULL)
  {
    aux->Dato = A->Dato;
    aux = A;
    A = A->izq;
  }
  else
    reemplazar(A->der, aux);
}*/


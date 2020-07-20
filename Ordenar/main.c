#include "arbolB.h"
void menu(ARBOL);
int main(){
	ARBOL A;
	A = crear();
	menu(A);
return 0 ;
}

void menu(ARBOL A){
	int o;
	int opc,e,b,el,s,nume = 0,p= 0,i =0, h = 0;
	
	o == 1;
	printf("\n\nPrograma Arbol Binario.\n\n");
	while(o!= 9){	
	printf("\n¿Que desea realizar?\n");
	printf("1.-Llenar arbol\n");
	printf("2.-buscar elemento\n");
	printf("3.-Eliminar\n");
	printf("4.-mostrar inOrden\n");
	printf("5.-Mostrar PostOrden\n");
	printf("6.-Mostrar PreOrden \n");
	printf("7.-Numero de elementos\n");
	printf("8.-Altura del arbol\n");
	printf("9.-Salir\n");
	scanf("%d",&o);
	printf("\n");
	switch(o){
	case 1:
	
	opc = 1;
	
	while( opc == 1){
	printf("Ingresa los elementos del arbol:\n ");
	scanf("%d", &e);
	insertar(&A, e);
	printf("¿desea ingresar mas elementos?\n");
	scanf("%d",&opc);
}
	break;
	case 2: 
	
	printf("Ingrese el elemento a buscar:\n");	
	scanf("%d",&b);
	s = buscar(A,b);
	if(s == 1)
		printf("EL elemento se encuentra en el arbol");
	if(s == 0)
		printf("EL elemento no se encuentra en el arbol");
	break;
	case 3:
	printf("Ingrese el elemento a eliminar:\n");	
	scanf("%d",&el);
	borrar(A,el);
	break;
	case 4:
	inOrden(A);
	break;
	case 5:
	postOrden(A);
	break;
	case 6:
	preOrden(A);
	break;
	case 7:
	nume = numElementos(A,nume);
	printf("El numero de elementos del arbol son: %d \n",nume);
	break;
	case 8:
	h = AlturaArbol(A,h);
	printf("La altura del arbol es: %d\n", h);
	break;
	case 9:
	exit(0);
	break;
}


}

}

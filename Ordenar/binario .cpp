#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;
int fact(int);
int combinacion(int[],char[],int,int);
void universo(int);
void menu();
int main(){
	menu();
	return 0;
}
int fact(int n){
	int r; 
	if (n==1){
		return 1; 
	} 
	r=n*fact(n-1) ; 
	return (r ) ; 
}

int combinacion(int i[], char r[],int l,int k){		
		if(l == k){
			ofstream archivo;
			archivo.open("binario.txt",ios::app); 
			archivo<<r<<",";
			return 0;
		}
		for(int j = 0; j<2;j++){
			if(i[j] == 0) return 0;
			if(j == 0){
			r[l] =  '0';
			i[j]--;
			combinacion(i,r,l+1,k);
			i[j]++; 
		}
			if(j == 1){
			r[l] =  '1';
			i[j]--;
			combinacion(i,r,l+1,k);
			i[j]++;
		}
		}
			
	} 
void universo(int k){
	int r,p,nc,c,i,n,b,a,d = 0,n0= 0,n1= 0;
	ofstream fich("binario.txt"); 
	ofstream archivo;
	archivo.open("binario.txt",ios::app); 
	if(k == -1){
	srand (time(NULL));
	r = rand()%15;}
	if(k == 0)
		archivo <<"{e}";
	if(k == 1)
		archivo <<"{e,0,1}";
	if(k == 2)
	archivo <<"{e,0,1,00,01,10,11}";
	if(k >2)
		r = k;
		archivo <<"{e,0,1,00,01,10,11,";
		archivo.close();
	for(p = 3; p<r ;p++){
		char binario [p];
		for( i = 0;i<=p;i++){
				binario[i] = '0';
				if (i == p)
				binario[i] = '\0';
			}
		archivo.open("binario.txt",ios::app);
		archivo << binario<< ",";		
		archivo.close();
			
		for(nc = 1;nc<p; nc++){
			
			c = fact(p)/(fact(nc)*fact(p-nc));
			
				for(a = 0; a<(p-nc);a++){
					binario[a] = '0';
					n0++;
					}
				for(a; a<p;a++){
					binario[a] = '1';
					n1++;
					}
				archivo.open("binario.txt",ios::app);
				archivo << binario<< ",";		
				archivo.close();
				printf("%s,",binario);
				int cont[2];
				cont[0] = n0;
				cont[1] = n1;
				char comb [4] ;	
				combinacion(cont,comb,0,p);
				n0 = 0;
				n1 = 0;
		}
		for( i = 0;i<=p;i++){
				binario[i] = '1'; 
				if (i == p)
				binario[i] = '\0';
			}
		archivo.open("binario.txt",ios::app);
		archivo << binario<< ",";		
		archivo.close();
	}
	archivo<<"}";
	
	
	
}
void menu(){
	int opc = 0,k = 0;
	do{
	
	printf("1.-Introducir k manualmente\n");
	printf("2.-Automatico\n");
	printf("3.-Salir\n");
	scanf("%d",&opc);
	switch(opc){
		case 1:
			printf("Introdusca k");
			scanf("%d",&k);
			universo(k);
		break;
		case 2:
			universo(-1);
			break;
		case 3:
			exit(1);
	}
}
	while(opc != 3);
	
	
}







	
	


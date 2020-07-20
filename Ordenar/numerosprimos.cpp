#include <stdio.h>
#include <string.h>
#include <fstream>
#include <math.h>
using namespace std;
int convertir(char *);
void esprimo(int,char*);
int leer();

int main(){
	leer();
	return 0;
}
int leer()
{
   char s2[2] =",";
   char* s3;
   string binario;
   char *ptr;
	ifstream arch;
	arch.open("binario.txt",ios::in);
	while(!arch.eof()){
		getline(arch,binario);
		}	
	s3 = strdup(binario.c_str());
   ptr = strtok( s3, s2 );    
   //printf( "%s\n", ptr );
   while( (ptr = strtok( NULL, s2 )) != NULL ) {
   
     //printf( "\n%s", ptr );
	 esprimo(convertir(ptr),ptr);
	 }
   return 0;
}

int convertir(char *Bin){
	int  b,i,n;
	int  tam;
	int  decimal = 0;

	tam = strlen(Bin) - 1;
	for(i = 0; i <= tam; i++){ 	
		b = 1; 	
		n = (Bin[i] - '0');  	
		b = b<<(tam-i);
	decimal = decimal + n * b;
	}

	return(decimal);
	}
	

void esprimo(int n, char*b){

	ofstream archivo;
	
 		int a=0;
 		for(int i=1;i<=100000;i++){
     		if(n%i==0) 
     		a++;
 	}
 	if (a==2){ 
 	archivo.open("numeros_primos.txt",ios::app);
 	archivo<<n<<"  "<<b<<"\n";
 	printf("%d    %s\n",n,b);
	 }
 	
 	

}
